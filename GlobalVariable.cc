
#include <cstdio>
#include <map>
#include <string>
#include <unordered_set>
#include <iterator>

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTDumperUtils.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/Decl.h"

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/FileManager.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/AST/ASTTypeTraits.h"

#include "clang/AST/Expr.h"
#include "clang/AST/ParentMapContext.h"
#include "clang/AST/DeclBase.h"
#include "clang/Tooling/Refactoring/RecursiveSymbolVisitor.h"

using namespace clang;

std::map<VarDecl*, std::set<std::string>> globalVarReferences;

class GlobalVariableVisitor : public RecursiveASTVisitor<GlobalVariableVisitor> {
private:
	clang::ASTContext *context;
	CompilerInstance& instance;

	clang::DiagnosticsEngine& d;
	std::map<std::string, std::map<int, int>> functionSpan;

	unsigned int warningID;

	bool isInHeader(Decl *decl) {
		auto loc = decl->getLocation();
		auto floc = context->getFullLoc(loc);
		if (floc.isInSystemHeader()) return true;
		auto entry = floc.getFileEntry()->getName();
		if (entry.endswith(".h") || entry.endswith(".hpp")) {
			return true;
		}
		return false;
	}


public:
	explicit GlobalVariableVisitor(ASTContext *context, CompilerInstance& instance): 
			context(context), instance(instance), d(instance.getDiagnostics()) {
		warningID = d.getCustomDiagID(DiagnosticsEngine::Warning,
				"Name beginning with underscore: '%0'");
	}

	void displayDiag(SourceLocation loc, std::string varName, std::string funcName){
		d.Report(context->getFullLoc(loc), 
		d.getCustomDiagID(DiagnosticsEngine::Warning, "Bad Implementation of Global Variable '%0' Found in '%1'")) 
		<< varName << funcName;
	}

	virtual bool VisitFunctionDecl(FunctionDecl *d) {
		if (isInHeader(d)) {
			return true;
		}
		auto funBeginLoc = context->getFullLoc((d->getBeginLoc()));
		auto funEndLoc = context->getFullLoc((d->getEndLoc()));
		if(funBeginLoc.isValid() && funEndLoc.isValid()){
			functionSpan[d->getNameAsString().c_str()].insert({funBeginLoc.getSpellingLineNumber(), funEndLoc.getSpellingLineNumber()});
		}
		return true;
	}

	virtual bool VisitVarDecl(VarDecl *var) {
		if (isInHeader(var)) {
			return true;
		}
		else if (var->hasGlobalStorage()){
			globalVarReferences[var] = std::set<std::string> {};
		}
		return true;
	}

	virtual bool VisitDeclRefExpr(const DeclRefExpr *d) {

		const auto decl = d->getDecl();
		 
		const auto referencedDecl = d->getReferencedDeclOfCallee();

		VarDecl* var;
		if(referencedDecl) var = (VarDecl*)cast<VarDecl>(referencedDecl);
		if(var && globalVarReferences.count(var)){ 
			auto varLoc = context->getFullLoc((d->getLocation())).getSpellingLineNumber();
			for(auto function: functionSpan){
				auto funcName= function.first;
				auto lines = *function.second.begin();
				if(varLoc >= lines.first && varLoc <= lines.second){
					globalVarReferences[var].insert(funcName.c_str());
					break;
				}
			}

			return true;
		}
		return true;		
	}
};

class GlobalVariableConsumer : public ASTConsumer {
	CompilerInstance& instance;
	GlobalVariableVisitor visitor;

public:
	GlobalVariableConsumer(CompilerInstance& instance)
			: instance(instance), visitor(&instance.getASTContext(), instance) {}
 
	void showGlobalVariables(){
		std::map<VarDecl*, std::set<std::string>>::iterator itr;
		for (itr = globalVarReferences.begin(); itr != globalVarReferences.end(); ++itr) {
			std::set<std::string> temp = itr->second;

			if(temp.size() > 1){
				continue;
			}
			for (auto temp_itr = temp.begin(); temp_itr != temp.end(); temp_itr++) {

				visitor.getDerived().displayDiag(itr->first->getLocation(), itr->first->getNameAsString(), (temp_itr)->c_str());

			}
    	}	
	}

	virtual void HandleTranslationUnit(ASTContext &context) override {
		visitor.TraverseDecl(context.getTranslationUnitDecl());
		showGlobalVariables();
	}
};

class GlobalVariableAction : public PluginASTAction {
protected:
	virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& instance, llvm::StringRef) override {
		return std::make_unique<GlobalVariableConsumer>(instance);
	}

	virtual bool ParseArgs(const CompilerInstance&, const std::vector<std::string>&) override {
		return true;
	}

	virtual PluginASTAction::ActionType getActionType() override {
  		return PluginASTAction::AddAfterMainAction;
	}
};

static FrontendPluginRegistry::Add<GlobalVariableAction> GlobalVariable("GlobalVariable", "Warn against global variable being used locally");

