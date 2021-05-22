
#ifndef AST_H
#define AST_H

#include "clang/AST/AST.h"
#include <memory>
//#include "clang/AST/ASTConsumer.h"
//#include "clang/AST/Expr.h"
//#include "clang/AST/Stmt.h"


namespace ast{

using RealScalar = double;

using UnitDecl = const clang::TranslationUnitDecl;
using FuncDecl = const clang::FunctionDecl;
using Stmt = const clang::Stmt;
using VarDecl = const clang::VarDecl;
using ConsDecl = const clang::CXXConstructorDecl;
using ParamDecl = const clang::ParmVarDecl;


union ASTNode {
	UnitDecl* UnitDecl_;
	FuncDecl* FuncDecl_;
	Stmt* Stmt_;
	VarDecl* VarDecl_;
	ConsDecl* ConsDecl_;
	ParamDecl* ParamDecl_;
};

enum class ASTTag { UnitDecl__, FuncDecl__, Stmt__, VarDecl__, ConsDecl__, ParamDecl__ };
struct NodeContainer{
	NodeContainer(){};
	ASTTag ASTTag_;
	ASTNode ASTNode_;
};

std::shared_ptr<NodeContainer> mkContainer (UnitDecl* unitDecl);
std::shared_ptr<NodeContainer> mkContainer (FuncDecl* funcDecl);
std::shared_ptr<NodeContainer> mkContainer (Stmt* stmt);
std::shared_ptr<NodeContainer> mkContainer (VarDecl* varDecl);
std::shared_ptr<NodeContainer> mkContainer (ConsDecl* consDecl);
std::shared_ptr<NodeContainer> mkContainer (ParamDecl* paramDecl);

} // namespace

#endif

