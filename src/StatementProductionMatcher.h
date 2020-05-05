

#ifndef statem
#define statem
#include "BaseMatcher.h"
#include "Interpretation.h"

/*
See BaseMatcher.h for method details
Searches for relevant statements including physical calculations, generally inside a "compound" statement in a code block
*/
/*
STMT := VEC_VAR = EXPR | SCALAR_VAR = SCALAR_EXPR  | VEC_EXPR | SCALAR_EXPR | DECL VEC_VAR = VEC_EXPR | DECL SCALAR_VAR = SCALAR_EXPR
*/
class StatementProductionMatcher : public BaseMatcher {
public:
    StatementProductionMatcher(clang::ASTContext* context, interp::Interpretation* interp) : BaseMatcher(context, interp) {}
    virtual void search();
    virtual void run(const MatchFinder::MatchResult &Result);

};

#endif