
#ifndef BRIDGE_H
#define BRIDGE_H

#ifndef leanInferenceWildcard
#define leanInferenceWildcard "_"
#endif

#include <cstddef>  
#include "clang/AST/AST.h"
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>

//#include "AST.h"
#include "Coords.h"

//#include <g3log/g3log.hpp>


using namespace std;

/*
- Space
- Ident
- Expr
- Value
- Defn
*/

namespace domain{

class DomainObject;
class DomainContainer;
template<typename ValueType,int ValueCount>
class ValueObject;

class CoordinateSpace;
class StandardSpace;
template<int Dimension>
class DerivedSpace;

class TimeCoordinateSpace;
class StandardTimeCoordinateSpace;
class DerivedTimeCoordinateSpace;

class Geom1DCoordinateSpace;
class StandardGeom1DCoordinateSpace;
class DerivedGeom1DCoordinateSpace;

class Scalar;

class Duration;
class Time;
class TimeTransform;

class Displacement;
class Position;
class Geom1DTransform;
            
// Definition for Domain class 
using string = std::string;

class Domain {
public:
    DomainContainer* mkDefaultDomainContainer();
    DomainContainer* mkDefaultDomainContainer(std::initializer_list<DomainContainer*> operands);
    DomainContainer* mkDefaultDomainContainer(std::vector<DomainContainer*> operands);
    //DomainContainer* mkDefaultDomainContainer(std::initializer_list<DomainContainer*> operands);
    /*DomainContainer* mkDefaultDomainContainer(std::vector<DomainContainer*> operands){
        std::vector<DomainObject*> ops = {std::transform(operands.begin(), operands.end(), s.begin(),
                   [](DomainContainer* d) -> DomainObject* { return dynamic_cast<DomainObject*>(d) })};
        return mkDefaultDomainContainer(ops);
    }*/

    StandardTimeCoordinateSpace* mkStandardTimeCoordinateSpace(string name);
    DerivedTimeCoordinateSpace* mkDerivedTimeCoordinateSpace(string name, TimeCoordinateSpace* parent, float* originData, float** basisData);

    StandardGeom1DCoordinateSpace* mkStandardGeom1DCoordinateSpace(string name);
    DerivedGeom1DCoordinateSpace* mkDerivedGeom1DCoordinateSpace(string name, Geom1DCoordinateSpace* parent, float* originData, float** basisData);

    Scalar* mkScalar(string name, float* value);

    Duration* mkDuration(string name, TimeCoordinateSpace* parent, float* value);
    Time* mkTime(string name, TimeCoordinateSpace* parent, float* value);
    TimeTransform* mkTimeTransform(string name, TimeCoordinateSpace* domain_, TimeCoordinateSpace* codomain_); 

    Displacement* mkDisplacement(string name, Geom1DCoordinateSpace* parent, float* value);
    Position* mkPosition(string name, Geom1DCoordinateSpace* parent, float* value);
    Geom1DTransform* mkGeom1DTransform(string name, Geom1DCoordinateSpace* domain_, Geom1DCoordinateSpace* codomain_); 

    std::vector<TimeCoordinateSpace*> getTimeSpaces() const {return timeSpaces;};
    std::vector<Geom1DCoordinateSpace*> getGeom1DSpaces() const {return geom1dSpaces;};
    std::vector<CoordinateSpace*> getSpaces() const {return spaces;};
private:
    std::vector<TimeCoordinateSpace*> timeSpaces;
    std::vector<Geom1DCoordinateSpace*> geom1dSpaces;
    std::vector<CoordinateSpace*> spaces;
};
class DomainObject {
public:
    DomainObject(std::initializer_list<DomainObject*> args);
    DomainObject(std::vector<DomainObject*> operands) : operands_(operands) {};
    DomainObject(){};
    DomainObject(string name_) : name(name_) {};
    virtual ~DomainObject(){};
    DomainObject* getOperand(int i);
    std::vector<DomainObject*> getOperands() const { return operands_; };
    void setOperands(std::vector<DomainObject*> operands);

    virtual std::string toString() const { return "Bad code if called!"; }
    friend class DomainObject; 

    std::string getName() const {
        return name;
    }
  
protected:
    std::vector<DomainObject*> operands_;
    int operand_count;
    std::string name;
};

class ErrorObject : public DomainObject {
public:
    ErrorObject() : DomainObject() {};
    ErrorObject(std::string error_str_) : DomainObject(), error_str(error_str_) {};
    virtual std::string toString() const override {
        return std::string("Error Detected");
    }

    virtual std::string toErrorString() const {
        return std::string("") + error_str;
    }

private:
    std::string error_str;
};

enum class AnnotationState { Unannotated =1, Manual=2, Inferred=3, Error=4 };


class DomainContainer : public DomainObject{
public:
        DomainContainer() : DomainObject(), inner_(nullptr), as_(AnnotationState::Unannotated) {};
        DomainContainer(DomainObject* inner) : inner_(inner), as_(AnnotationState::Unannotated) {};
        DomainContainer(std::initializer_list<DomainObject*> operands);
        DomainContainer(std::vector<DomainObject*> operands);
        DomainContainer(std::initializer_list<DomainContainer*> operands);
        DomainContainer(std::vector<DomainContainer*> operands);
        virtual std::string toString() const override;// { this->hasValue() ? this->inner_->toString() : "No Provided Interpretation"; }
        DomainObject* getValue() const { return this->inner_; }
        void setValue(DomainObject* obj);
        bool hasValue() const;
        void setAnnotationState(AnnotationState as){
            this->as_ = as;
        };
        AnnotationState getAnnotationState(){
            return this->as_;
        }

        std::string getAnnotationStateStr(){
            return 
                this->as_ == AnnotationState::Unannotated ? "Unannotated" :
                   this->as_ == AnnotationState::Manual ? "Manual" :
                    this->as_ == AnnotationState::Inferred ? "Inferred" :
                    this->as_ == AnnotationState::Error ? "Error" : "";
        };

private:
    DomainObject* inner_;
    AnnotationState as_;
};

class CoordinateSpace : public DomainObject {
public:
    CoordinateSpace(){};
    virtual ~CoordinateSpace(){};
    CoordinateSpace(std::string name_) : name(name_) {};
    std::string getName() const { return name; };
private:
    std::string name;
};

class StandardSpace : public CoordinateSpace {
public:
    virtual ~StandardSpace(){};
    StandardSpace() {};
private:
};

template<int Dimension>
class DerivedSpace : public CoordinateSpace {
public:
    virtual ~DerivedSpace() {
        delete originData;
        delete basisData;
    };
    DerivedSpace(){
        originData = new float[Dimension];
        basisData = new float*[Dimension];
        for(int i = 0;i<Dimension;i++)
            basisData[i] = new float[Dimension];
    }
    DerivedSpace(CoordinateSpace* parentSpace_) : DerivedSpace() {
        parentSpace = parentSpace_;
    };
    DerivedSpace(CoordinateSpace* parentSpace_, float* originData_, float** basisData_) 
        : DerivedSpace(parentSpace_){
        originData = originData_;
        basisData = basisData_;
        //setOrigin(originData_);
        //setBasis(basisData_);
    };
    DerivedSpace(float* originData_, float** basisData_) : DerivedSpace() {
        originData = originData;
        basisData = basisData_;
        //setOrigin(originData_);
        //setBasis(basisData_);
    };

    float* getOrigin() const { return originData; };//work on this
    float** getBasis() const { return basisData; };
    void setOrigin(float* originData_){
        for(auto i = 0;i<Dimension;i++){
            originData[i] = originData_[i];
        }
    };
    void setBasis(float** basisData_){
        for(auto i = 0;i<Dimension;i++){
            for(auto j = 0;j<Dimension;j++){
                basisData[i][j] = basisData_[i][j];
            }
        }
    };

    CoordinateSpace* getParent() const { return parentSpace; }
protected:
    float* originData;
    float** basisData;
    CoordinateSpace* parentSpace;
};

class TimeCoordinateSpace : public CoordinateSpace {
public:
    TimeCoordinateSpace(std::string name) : CoordinateSpace(name) {};
private:
};

//it's a... diamond
class StandardTimeCoordinateSpace : public TimeCoordinateSpace, public StandardSpace {
public:
    StandardTimeCoordinateSpace(std::string name) : TimeCoordinateSpace(name) {};

    virtual std::string toString() const override{
        return TimeCoordinateSpace::getName() + " StandardTimeCoordinateSpace()";
    };
private:
};

class DerivedTimeCoordinateSpace : public TimeCoordinateSpace, public DerivedSpace<1> {
public:
    DerivedTimeCoordinateSpace(std::string name, 
        TimeCoordinateSpace* parentSpace_, float* originData, float** basisData)
        : TimeCoordinateSpace(name), DerivedSpace<1>(parentSpace_,originData, basisData){};//, parentSpace(parentSpace_) {};
    TimeCoordinateSpace* getParent() const {
        return dynamic_cast<TimeCoordinateSpace*>(DerivedSpace::getParent());
    }
    virtual std::string toString() const override{
        return TimeCoordinateSpace::getName() + " DerivedTimeCoordinateSpace(parent:" 
            + this->getParent()->getName() + ",origin:" + std::to_string(originData[0]) + ",basis:" + std::to_string(basisData[0][0]) + ")";
    };

private:
    //--TimeCoordinateSpace* parentSpace;
};


class Geom1DCoordinateSpace : public CoordinateSpace {
public:
    Geom1DCoordinateSpace(std::string name) : CoordinateSpace(name) {};
private:
};

//it's a... diamond
class StandardGeom1DCoordinateSpace : public Geom1DCoordinateSpace, public StandardSpace {
public:
    StandardGeom1DCoordinateSpace(std::string name) : Geom1DCoordinateSpace(name) {};

    virtual std::string toString() const override{
        return Geom1DCoordinateSpace::getName() + " StandardGeom1DCoordinateSpace()";
    };
private:
};

class DerivedGeom1DCoordinateSpace : public Geom1DCoordinateSpace, public DerivedSpace<1> {
public:
    DerivedGeom1DCoordinateSpace(std::string name, 
        Geom1DCoordinateSpace* parentSpace_, float* originData, float** basisData)
        : Geom1DCoordinateSpace(name), DerivedSpace<1>(parentSpace_,originData, basisData){};//, parentSpace(parentSpace_) {};
    Geom1DCoordinateSpace* getParent() const {
        return dynamic_cast<Geom1DCoordinateSpace*>(DerivedSpace::getParent());
    }
    virtual std::string toString() const override{
        return Geom1DCoordinateSpace::getName() + " DerivedGeom1DCoordinateSpace(parent:" 
            + this->getParent()->getName() + ",origin:" + std::to_string(originData[0]) + ",basis:" + std::to_string(basisData[0][0]) + ")";
    };

private:
    //--Geom1DCoordinateSpace* parentSpace;
};




class CoordinateSpaceTransform : public DomainObject {
public:
    CoordinateSpaceTransform(std::string name, CoordinateSpace* domain_, CoordinateSpace* codomain_)
        : DomainObject(name), domain(domain_), codomain(codomain_) {};
protected:
    CoordinateSpace* domain;
    CoordinateSpace* codomain;
};

class Duration : public DomainObject {
public:
    Duration(std::string name_, TimeCoordinateSpace* sp, float* value_) 
        : DomainObject(name_), space(sp), value(value_) {};
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Duration(") + space->getName() + "," + std::to_string(value[0]) + ")"; 
    };
    virtual TimeCoordinateSpace* getSpace() const { return space; };
    virtual float* getValue() const { return value; };
private:
    TimeCoordinateSpace* space;
    float* value;
};

class Time : public DomainObject {
public:
    Time(std::string name_, TimeCoordinateSpace* sp, float* value_) 
        : DomainObject(name_), space(sp), value(value_) {};
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Time(") + space->getName() + "," + std::to_string(value[0]) + ")"; 
    };
    virtual TimeCoordinateSpace* getSpace() const { return space; };
    virtual float* getValue() const { return value; };
private:
    TimeCoordinateSpace* space;
    float* value;
};

class Displacement : public DomainObject {
public:
    Displacement(std::string name_, Geom1DCoordinateSpace* sp, float* value_) 
        : DomainObject(name_), space(sp), value(value_) {};
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Displacement(") + space->getName() + "," + std::to_string(value[0]) + ")"; 
    };
    virtual Geom1DCoordinateSpace* getSpace() const { return space; };
    virtual float* getValue() const { return value; };
private:
    Geom1DCoordinateSpace* space;
    float* value;
};

class Position : public DomainObject {
public:
    Position(std::string name_, Geom1DCoordinateSpace* sp, float* value_) 
        : DomainObject(name_), space(sp), value(value_) {};
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Position(") + space->getName() + "," + std::to_string(value[0]) + ")"; 
    };
    virtual Geom1DCoordinateSpace* getSpace() const { return space; };
    virtual float* getValue() const { return value; };
private:
    Geom1DCoordinateSpace* space;
    float* value;
};


class Scalar : public DomainObject {
public:
    Scalar(std::string name_, float* value_)
        : DomainObject(name_), value(value_) {};
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Scalar(") + std::to_string(value[0]) + ")"; 
    };
    virtual float* getValue() const { return value; };
private:
    float* value;
};

class TimeTransform : public CoordinateSpaceTransform {
public:
    TimeTransform(std::string name, TimeCoordinateSpace* domain, TimeCoordinateSpace* codomain)
        : CoordinateSpaceTransform(name, domain, codomain) {};
    TimeCoordinateSpace* getDomain() const {
        return static_cast<TimeCoordinateSpace*>(domain);
    };
    TimeCoordinateSpace* getCodomain() const {
        return static_cast<TimeCoordinateSpace*>(codomain);
    };
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("TimeTransform(") + this->getDomain()->getName() + "," + this->getCodomain()->getName() + ")"; 
    }
private:
};

class Geom1DTransform : public CoordinateSpaceTransform {
public:
    Geom1DTransform(std::string name, Geom1DCoordinateSpace* domain, Geom1DCoordinateSpace* codomain)
        : CoordinateSpaceTransform(name, domain, codomain) {};
    Geom1DCoordinateSpace* getDomain() const {
        return static_cast<Geom1DCoordinateSpace*>(domain);
    };
    Geom1DCoordinateSpace* getCodomain() const {
        return static_cast<Geom1DCoordinateSpace*>(codomain);
    };
    virtual std::string toString() const override {
        return this->getName() + " " + std::string("Geom1DTransform(") + this->getDomain()->getName() + "," + this->getCodomain()->getName() + ")"; 
    }
private:
};

} // end namespace

#endif