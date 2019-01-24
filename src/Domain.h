#ifndef DOMAIN_H
#define DOMAIN_H

#include <list>
#include <string>

using namespace std;

class Space {
public:
	Space() : name_("") {};
	Space(string name) : name_(name) {};
private:
	string name_;
};

class Vector {
private:
	Space space_;
public:
	Vector();
	Vector(Space& space);
};

class Expression {
private:
	Vector& v1_;
	Vector& v2_;
public:
	Expression();
	Expression(Vector& v1, Vector& v2);
};

class Domain {

public:

	// Add new space,, s, to domain
	// Precondition: true
	// Postcondition: 
	//	spaces' = spaces + s and
	//  return value = reference to s
	Space& addSpace(const string& name);

	// Add new vector, v, in space s, to domain
	// Precondition: s is already in spaces
	// Postcondition: vectors' = vectors + v
	Vector& addVector(Space& s);

	// Add new plus expression, e, to domain
	// Precondition: v1 and v2 already in vectors
	// Postcondition: expressions' = expressions + e
	//	where e has v1 and v2 as its arguments
	Expression& addExpression(Vector& v1, Vector& v2);

	// Check domain for consistency
	// Precondition: true
	// Postcondition: return value true indicates presence of inconsistencies
	bool isInconsistent();

	/*
	Methods by which clients can learn what's in this domain.
	*/

	list<Space>& getSpaces();
	
private:
	list<Space> spaces;
	list<Vector> vectors;
	list<Expression> expression;
};

#endif