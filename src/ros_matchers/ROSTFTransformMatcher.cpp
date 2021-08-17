
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include "ROSBooleanMatcher.h"
#include "ROSBoolMatcher.h"
#include "FloatMatcher.h"
#include "DoubleMatcher.h"
#include "ROSTFScalarMatcher.h"
#include "ROSTimeMatcher.h"
#include "ROSTimeBaseMatcher.h"
#include "ROSDurationBaseMatcher.h"
#include "ROSDurationMatcher.h"
#include "ROSDurationBaseMatcher.h"
#include "ROSTFVector3Matcher.h"
#include "ROSTF2DurationMatcher.h"
#include "ROSTFTransformMatcher.h"
#include "VoidMatcher.h"
#include "ROSGeometryPoseWithCovarianceStamped.h"
#include "ROSGeomQuaternion.h"
#include "ROSTFQuaternion.h"
#include "ROSTF2Quaternion.h"
#include "ROSTF2Vector3Matcher.h"
#include "ROSTF2TransformStamped.h"
#include "ROSTF2Transform.h"
#include "ROSGeomPoseStamped.h"
#include "ROSGeomTransformStamped.h"


#include <string>
#include <unordered_map>
#include <functional>


void ROSTFTransformMatcher::setup(){
		StatementMatcher cxxConstructExpr_=cxxConstructExpr().bind("CXXConstructExpr");
		localFinder_.addMatcher(cxxConstructExpr_,this);
	
		StatementMatcher callExpr_=callExpr().bind("CallExpr");
		localFinder_.addMatcher(callExpr_,this);
	
		StatementMatcher memberExpr_=memberExpr().bind("MemberExpr");
		localFinder_.addMatcher(memberExpr_,this);
	
		StatementMatcher implicitCastExpr_=implicitCastExpr().bind("ImplicitCastExpr");
		localFinder_.addMatcher(implicitCastExpr_,this);
	
		StatementMatcher cxxBindTemporaryExpr_=cxxBindTemporaryExpr().bind("CXXBindTemporaryExpr");
		localFinder_.addMatcher(cxxBindTemporaryExpr_,this);
	
		StatementMatcher materializeTemporaryExpr_=materializeTemporaryExpr().bind("MaterializeTemporaryExpr");
		localFinder_.addMatcher(materializeTemporaryExpr_,this);
	
		StatementMatcher parenExpr_=parenExpr().bind("ParenExpr");
		localFinder_.addMatcher(parenExpr_,this);
	
		StatementMatcher exprWithCleanups_=exprWithCleanups().bind("ExprWithCleanups");
		localFinder_.addMatcher(exprWithCleanups_,this);
	
		StatementMatcher cxxFunctionalCastExpr_=cxxFunctionalCastExpr().bind("CXXFunctionalCastExpr");
		localFinder_.addMatcher(cxxFunctionalCastExpr_,this);
	
		StatementMatcher cxxOperatorCallExpr_=cxxOperatorCallExpr().bind("CXXOperatorCallExpr");
		localFinder_.addMatcher(cxxOperatorCallExpr_,this);
	
		StatementMatcher declRefExpr_=declRefExpr().bind("DeclRefExpr");
		localFinder_.addMatcher(declRefExpr_,this);
	
		StatementMatcher cxxMemberCallExpr_=cxxMemberCallExpr().bind("CXXMemberCallExpr");
		localFinder_.addMatcher(cxxMemberCallExpr_,this);
    this->childExprStore_ = nullptr;
};

void ROSTFTransformMatcher::run(const MatchFinder::MatchResult &Result){
    if(this->childExprStore_ != nullptr){
        return;
    }
	auto cxxConstructExpr_ = Result.Nodes.getNodeAs<clang::CXXConstructExpr>("CXXConstructExpr");
	
	auto callExpr_ = Result.Nodes.getNodeAs<clang::CallExpr>("CallExpr");
	
	auto memberExpr_ = Result.Nodes.getNodeAs<clang::MemberExpr>("MemberExpr");
	
	auto implicitCastExpr_ = Result.Nodes.getNodeAs<clang::ImplicitCastExpr>("ImplicitCastExpr");
	
	auto cxxBindTemporaryExpr_ = Result.Nodes.getNodeAs<clang::CXXBindTemporaryExpr>("CXXBindTemporaryExpr");
	
	auto materializeTemporaryExpr_ = Result.Nodes.getNodeAs<clang::MaterializeTemporaryExpr>("MaterializeTemporaryExpr");
	
	auto parenExpr_ = Result.Nodes.getNodeAs<clang::ParenExpr>("ParenExpr");
	
	auto exprWithCleanups_ = Result.Nodes.getNodeAs<clang::ExprWithCleanups>("ExprWithCleanups");
	
	auto cxxFunctionalCastExpr_ = Result.Nodes.getNodeAs<clang::CXXFunctionalCastExpr>("CXXFunctionalCastExpr");
	
	auto cxxOperatorCallExpr_ = Result.Nodes.getNodeAs<clang::CXXOperatorCallExpr>("CXXOperatorCallExpr");
	
	auto declRefExpr_ = Result.Nodes.getNodeAs<clang::DeclRefExpr>("DeclRefExpr");
	
	auto cxxMemberCallExpr_ = Result.Nodes.getNodeAs<clang::CXXMemberCallExpr>("CXXMemberCallExpr");
    std::unordered_map<std::string,std::function<bool(std::string)>> arg_decay_exist_predicates;
    std::unordered_map<std::string,std::function<std::string(std::string)>> arg_decay_match_predicates;

    if(cxxConstructExpr_){
        auto decl_ = cxxConstructExpr_->getConstructor();
        if(decl_->isCopyOrMoveConstructor())
        {
            ROSTFTransformMatcher pm{context_, interp_};
            pm.setup();
            pm.visit(**cxxConstructExpr_->getArgs());
            this->childExprStore_ = pm.getChildExprStore();
            if(this->childExprStore_){return;}
    
            else{
                this->childExprStore_ = (clang::Stmt*)cxxBindTemporaryExpr_;
                interp_->mkNode("LIT_R4X4",(clang::Stmt*)cxxBindTemporaryExpr_,true);
                return;
            }
        }
    }

	
	arg_decay_exist_predicates["callExpr_tf::Transform"] = [=](std::string typenm){
    if(false){return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
    else { return false; }
    };
    if(callExpr_){
        auto func_ = callExpr_->getDirectCallee();
        if(interp_->checkFuncExists(func_)){
            std::vector<const clang::Stmt*> operands_;
            for(auto arg : callExpr_->arguments()){
                std::string typestr = "";
                if(false){}
    
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorgeometry_msgs::PoseWithCovarianceStamped" or typestr =="geometry_msgs::PoseWithCovarianceStamped" or typestr == "const geometry_msgs::PoseWithCovarianceStamped" or typestr == "class geometry_msgs::PoseWithCovarianceStamped" or typestr == "const class geometry_msgs::PoseWithCovarianceStamped" or typestr ==  "::geometry_msgs::PoseWithCovarianceStamped_<allocator<void> >" or typestr == "operatorPoseWithCovarianceStamped" or typestr =="PoseWithCovarianceStamped" or typestr == "const PoseWithCovarianceStamped" or typestr == "class PoseWithCovarianceStamped" or typestr == "const class PoseWithCovarianceStamped" or typestr ==  "::PoseWithCovarianceStamped_<allocator<void> >"){
                    ROSGeometryPoseWithCovarianceStamped m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorgeometry_msgs::TransformStamped" or typestr =="geometry_msgs::TransformStamped" or typestr == "const geometry_msgs::TransformStamped" or typestr == "class geometry_msgs::TransformStamped" or typestr == "const class geometry_msgs::TransformStamped" or typestr ==  "::geometry_msgs::TransformStamped_<allocator<void> >" or typestr == "operatorTransformStamped" or typestr =="TransformStamped" or typestr == "const TransformStamped" or typestr == "class TransformStamped" or typestr == "const class TransformStamped" or typestr ==  "::TransformStamped_<allocator<void> >"){
                    ROSGeomTransformStamped m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,false);
                if(typestr == "operatortf2::Stamped<tf2::Transform>" or typestr =="tf2::Stamped<tf2::Transform>" or typestr == "const tf2::Stamped<tf2::Transform>" or typestr == "class tf2::Stamped<tf2::Transform>" or typestr == "const class tf2::Stamped<tf2::Transform>" or typestr ==  "::tf2::Stamped<tf2::Transform>_<allocator<void> >" or typestr == "operatorStamped<tf2::Transform>" or typestr =="Stamped<tf2::Transform>" or typestr == "const Stamped<tf2::Transform>" or typestr == "class Stamped<tf2::Transform>" or typestr == "const class Stamped<tf2::Transform>" or typestr ==  "::Stamped<tf2::Transform>_<allocator<void> >"){
                    ROSTF2TransformStamped m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorgeometry_msgs::PoseStamped" or typestr =="geometry_msgs::PoseStamped" or typestr == "const geometry_msgs::PoseStamped" or typestr == "class geometry_msgs::PoseStamped" or typestr == "const class geometry_msgs::PoseStamped" or typestr ==  "::geometry_msgs::PoseStamped_<allocator<void> >" or typestr == "operatorPoseStamped" or typestr =="PoseStamped" or typestr == "const PoseStamped" or typestr == "class PoseStamped" or typestr == "const class PoseStamped" or typestr ==  "::PoseStamped_<allocator<void> >"){
                    ROSGeomPoseStamped m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorgeometry_msgs::Quaternion" or typestr =="geometry_msgs::Quaternion" or typestr == "const geometry_msgs::Quaternion" or typestr == "class geometry_msgs::Quaternion" or typestr == "const class geometry_msgs::Quaternion" or typestr ==  "::geometry_msgs::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    ROSGeomQuaternion m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                    ROSDurationBaseMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                    ROSDurationBaseMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf2::Quaternion" or typestr =="tf2::Quaternion" or typestr == "const tf2::Quaternion" or typestr == "class tf2::Quaternion" or typestr == "const class tf2::Quaternion" or typestr ==  "::tf2::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    ROSTF2Quaternion m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf::Quaternion" or typestr =="tf::Quaternion" or typestr == "const tf::Quaternion" or typestr == "class tf::Quaternion" or typestr == "const class tf::Quaternion" or typestr ==  "::tf::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    ROSTFQuaternion m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf2::Transform" or typestr =="tf2::Transform" or typestr == "const tf2::Transform" or typestr == "class tf2::Transform" or typestr == "const class tf2::Transform" or typestr ==  "::tf2::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                    ROSTF2Transform m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorros::TimeBase" or typestr =="ros::TimeBase" or typestr == "const ros::TimeBase" or typestr == "class ros::TimeBase" or typestr == "const class ros::TimeBase" or typestr ==  "::ros::TimeBase_<allocator<void> >" or typestr == "operatorTimeBase" or typestr =="TimeBase" or typestr == "const TimeBase" or typestr == "class TimeBase" or typestr == "const class TimeBase" or typestr ==  "::TimeBase_<allocator<void> >"){
                    ROSTimeBaseMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorros::Duration" or typestr =="ros::Duration" or typestr == "const ros::Duration" or typestr == "class ros::Duration" or typestr == "const class ros::Duration" or typestr ==  "::ros::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                    ROSDurationMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf2::Duration" or typestr =="tf2::Duration" or typestr == "const tf2::Duration" or typestr == "class tf2::Duration" or typestr == "const class tf2::Duration" or typestr ==  "::tf2::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                    ROSTF2DurationMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                    ROSTFTransformMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf2::Vector3" or typestr =="tf2::Vector3" or typestr == "const tf2::Vector3" or typestr == "class tf2::Vector3" or typestr == "const class tf2::Vector3" or typestr ==  "::tf2::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                    ROSTF2Vector3Matcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortf::Vector3" or typestr =="tf::Vector3" or typestr == "const tf::Vector3" or typestr == "class tf::Vector3" or typestr == "const class tf::Vector3" or typestr ==  "::tf::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                    ROSTFVector3Matcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorros::Time" or typestr =="ros::Time" or typestr == "const ros::Time" or typestr == "class ros::Time" or typestr == "const class ros::Time" or typestr ==  "::ros::Time_<allocator<void> >" or typestr == "operatorTime" or typestr =="Time" or typestr == "const Time" or typestr == "class Time" or typestr == "const class Time" or typestr ==  "::Time_<allocator<void> >"){
                    ROSTimeMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatortfScalar" or typestr =="tfScalar" or typestr == "const tfScalar" or typestr == "class tfScalar" or typestr == "const class tfScalar" or typestr ==  "::tfScalar_<allocator<void> >"){
                    ROSTFScalarMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatordouble" or typestr =="double" or typestr == "const double" or typestr == "class double" or typestr == "const class double" or typestr ==  "::double_<allocator<void> >"){
                    DoubleMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operator_Bool" or typestr =="_Bool" or typestr == "const _Bool" or typestr == "class _Bool" or typestr == "const class _Bool" or typestr ==  "::_Bool_<allocator<void> >"){
                    ROSBoolMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorfloat" or typestr =="float" or typestr == "const float" or typestr == "class float" or typestr == "const class float" or typestr ==  "::float_<allocator<void> >"){
                    FloatMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorbool" or typestr =="bool" or typestr == "const bool" or typestr == "class bool" or typestr == "const class bool" or typestr ==  "::bool_<allocator<void> >"){
                    ROSBooleanMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
                typestr = this->getTypeAsString(arg,true);
                if(typestr == "operatorvoid" or typestr =="void" or typestr == "const void" or typestr == "class void" or typestr == "const class void" or typestr ==  "::void_<allocator<void> >"){
                    VoidMatcher m{ this->context_, this->interp_};
                    m.setup();
                    m.visit(*arg);
                    if (m.getChildExprStore())
                        operands_.push_back(m.getChildExprStore());
                    continue;
                }
            }
            interp_->buffer_link(func_);
            interp_->buffer_operands(operands_);
            interp_->mkNode("CALL_R4X4",callExpr_,true);
            this->childExprStore_ = (clang::Stmt*)callExpr_;
            return;
        }
    }

	
	arg_decay_exist_predicates["memberExpr_tf::Transform"] = [=](std::string typenm){
    if(false){return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
    else { return false; }
    };
    if(memberExpr_){
        auto inner = memberExpr_->getBase();
        auto typestr = this->getTypeAsString(inner,true);
        if(false){}
        else if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
            ROSTFTransformMatcher innerm{this->context_,this->interp_};
            innerm.setup();
            innerm.visit(*inner);
            this->childExprStore_ = (clang::Stmt*)innerm.getChildExprStore();
            return;
        }

    }

	
	arg_decay_exist_predicates["implicitCastExpr_tf::Transform"] = [=](std::string typenm){
        if(false){return false; }
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; } 
    };

    if (implicitCastExpr_)
    {
        auto inner = implicitCastExpr_->getSubExpr();
        auto typestr = this->getTypeAsString(inner,true);
        auto hasmemb = clang::dyn_cast<clang::MemberExpr>(inner);
        if(false){}
        else if(hasmemb){
            while(auto memb = clang::dyn_cast<clang::MemberExpr>(inner))
            {
                inner = memb->getBase();                
            }

            auto typestr = this->getTypeAsString(inner,true);
            if(auto asRef = clang::dyn_cast<clang::DeclRefExpr>(inner))
            {
        
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorgeometry_msgs::PoseWithCovarianceStamped" or typestr =="geometry_msgs::PoseWithCovarianceStamped" or typestr == "const geometry_msgs::PoseWithCovarianceStamped" or typestr == "class geometry_msgs::PoseWithCovarianceStamped" or typestr == "const class geometry_msgs::PoseWithCovarianceStamped" or typestr ==  "::geometry_msgs::PoseWithCovarianceStamped_<allocator<void> >" or typestr == "operatorPoseWithCovarianceStamped" or typestr =="PoseWithCovarianceStamped" or typestr == "const PoseWithCovarianceStamped" or typestr == "class PoseWithCovarianceStamped" or typestr == "const class PoseWithCovarianceStamped" or typestr ==  "::PoseWithCovarianceStamped_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorgeometry_msgs::TransformStamped" or typestr =="geometry_msgs::TransformStamped" or typestr == "const geometry_msgs::TransformStamped" or typestr == "class geometry_msgs::TransformStamped" or typestr == "const class geometry_msgs::TransformStamped" or typestr ==  "::geometry_msgs::TransformStamped_<allocator<void> >" or typestr == "operatorTransformStamped" or typestr =="TransformStamped" or typestr == "const TransformStamped" or typestr == "class TransformStamped" or typestr == "const class TransformStamped" or typestr ==  "::TransformStamped_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,false);
                if(typestr == "operatortf2::Stamped<tf2::Transform>" or typestr =="tf2::Stamped<tf2::Transform>" or typestr == "const tf2::Stamped<tf2::Transform>" or typestr == "class tf2::Stamped<tf2::Transform>" or typestr == "const class tf2::Stamped<tf2::Transform>" or typestr ==  "::tf2::Stamped<tf2::Transform>_<allocator<void> >" or typestr == "operatorStamped<tf2::Transform>" or typestr =="Stamped<tf2::Transform>" or typestr == "const Stamped<tf2::Transform>" or typestr == "class Stamped<tf2::Transform>" or typestr == "const class Stamped<tf2::Transform>" or typestr ==  "::Stamped<tf2::Transform>_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorgeometry_msgs::PoseStamped" or typestr =="geometry_msgs::PoseStamped" or typestr == "const geometry_msgs::PoseStamped" or typestr == "class geometry_msgs::PoseStamped" or typestr == "const class geometry_msgs::PoseStamped" or typestr ==  "::geometry_msgs::PoseStamped_<allocator<void> >" or typestr == "operatorPoseStamped" or typestr =="PoseStamped" or typestr == "const PoseStamped" or typestr == "class PoseStamped" or typestr == "const class PoseStamped" or typestr ==  "::PoseStamped_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorgeometry_msgs::Quaternion" or typestr =="geometry_msgs::Quaternion" or typestr == "const geometry_msgs::Quaternion" or typestr == "class geometry_msgs::Quaternion" or typestr == "const class geometry_msgs::Quaternion" or typestr ==  "::geometry_msgs::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf2::Quaternion" or typestr =="tf2::Quaternion" or typestr == "const tf2::Quaternion" or typestr == "class tf2::Quaternion" or typestr == "const class tf2::Quaternion" or typestr ==  "::tf2::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf::Quaternion" or typestr =="tf::Quaternion" or typestr == "const tf::Quaternion" or typestr == "class tf::Quaternion" or typestr == "const class tf::Quaternion" or typestr ==  "::tf::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf2::Transform" or typestr =="tf2::Transform" or typestr == "const tf2::Transform" or typestr == "class tf2::Transform" or typestr == "const class tf2::Transform" or typestr ==  "::tf2::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorros::TimeBase" or typestr =="ros::TimeBase" or typestr == "const ros::TimeBase" or typestr == "class ros::TimeBase" or typestr == "const class ros::TimeBase" or typestr ==  "::ros::TimeBase_<allocator<void> >" or typestr == "operatorTimeBase" or typestr =="TimeBase" or typestr == "const TimeBase" or typestr == "class TimeBase" or typestr == "const class TimeBase" or typestr ==  "::TimeBase_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorros::Duration" or typestr =="ros::Duration" or typestr == "const ros::Duration" or typestr == "class ros::Duration" or typestr == "const class ros::Duration" or typestr ==  "::ros::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf2::Duration" or typestr =="tf2::Duration" or typestr == "const tf2::Duration" or typestr == "class tf2::Duration" or typestr == "const class tf2::Duration" or typestr ==  "::tf2::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf2::Vector3" or typestr =="tf2::Vector3" or typestr == "const tf2::Vector3" or typestr == "class tf2::Vector3" or typestr == "const class tf2::Vector3" or typestr ==  "::tf2::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortf::Vector3" or typestr =="tf::Vector3" or typestr == "const tf::Vector3" or typestr == "class tf::Vector3" or typestr == "const class tf::Vector3" or typestr ==  "::tf::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorros::Time" or typestr =="ros::Time" or typestr == "const ros::Time" or typestr == "class ros::Time" or typestr == "const class ros::Time" or typestr ==  "::ros::Time_<allocator<void> >" or typestr == "operatorTime" or typestr =="Time" or typestr == "const Time" or typestr == "class Time" or typestr == "const class Time" or typestr ==  "::Time_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatortfScalar" or typestr =="tfScalar" or typestr == "const tfScalar" or typestr == "class tfScalar" or typestr == "const class tfScalar" or typestr ==  "::tfScalar_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatordouble" or typestr =="double" or typestr == "const double" or typestr == "class double" or typestr == "const class double" or typestr ==  "::double_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operator_Bool" or typestr =="_Bool" or typestr == "const _Bool" or typestr == "class _Bool" or typestr == "const class _Bool" or typestr ==  "::_Bool_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorfloat" or typestr =="float" or typestr == "const float" or typestr == "class float" or typestr == "const class float" or typestr ==  "::float_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorbool" or typestr =="bool" or typestr == "const bool" or typestr == "class bool" or typestr == "const class bool" or typestr ==  "::bool_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
    
                typestr = this->getTypeAsString(inner,true);
                if(typestr == "operatorvoid" or typestr =="void" or typestr == "const void" or typestr == "class void" or typestr == "const class void" or typestr ==  "::void_<allocator<void> >"){
                    if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                        interp_->buffer_container(vardecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                        interp_->buffer_container(paramdecl_);
                        this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                        interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                        return;
                    }
                    else {
                        std::cout<<"Can't find declaration\n";
                        asRef->getDecl()->dump();
                    }
                }
     
            }
            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
            interp_->mkNode("LIT_R4X4",(clang::Stmt*)implicitCastExpr_,true);
            return;

        }
        
        typestr = this->getTypeAsString(inner,true);
        if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
            ROSTFTransformMatcher innerm{this->context_,this->interp_};
            innerm.setup();
            innerm.visit(*inner);
            this->childExprStore_ = (clang::Stmt*)innerm.getChildExprStore();
            return;
        }
        else{
            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
            interp_->mkNode("LIT_R4X4",(clang::Stmt*)implicitCastExpr_,true);
            return;
        }
        /*else{
            
            if(auto hasmemb = clang::dyn_cast<clang::MemberExpr>(inner)){
                while(auto memb = clang::dyn_cast<clang::MemberExpr>(inner))
                {
                    inner = memb->getBase();                
                }

                auto typestr = this->getTypeAsString(inner,true);
                if(auto asRef = clang::dyn_cast<clang::DeclRefExpr>(inner))
                {
            
                    if(typestr == "operatorgeometry_msgs::PoseWithCovarianceStamped" or typestr =="geometry_msgs::PoseWithCovarianceStamped" or typestr == "const geometry_msgs::PoseWithCovarianceStamped" or typestr == "class geometry_msgs::PoseWithCovarianceStamped" or typestr == "const class geometry_msgs::PoseWithCovarianceStamped" or typestr ==  "::geometry_msgs::PoseWithCovarianceStamped_<allocator<void> >" or typestr == "operatorPoseWithCovarianceStamped" or typestr =="PoseWithCovarianceStamped" or typestr == "const PoseWithCovarianceStamped" or typestr == "class PoseWithCovarianceStamped" or typestr == "const class PoseWithCovarianceStamped" or typestr ==  "::PoseWithCovarianceStamped_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorgeometry_msgs::TransformStamped" or typestr =="geometry_msgs::TransformStamped" or typestr == "const geometry_msgs::TransformStamped" or typestr == "class geometry_msgs::TransformStamped" or typestr == "const class geometry_msgs::TransformStamped" or typestr ==  "::geometry_msgs::TransformStamped_<allocator<void> >" or typestr == "operatorTransformStamped" or typestr =="TransformStamped" or typestr == "const TransformStamped" or typestr == "class TransformStamped" or typestr == "const class TransformStamped" or typestr ==  "::TransformStamped_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf2::Stamped<tf2::Transform>" or typestr =="tf2::Stamped<tf2::Transform>" or typestr == "const tf2::Stamped<tf2::Transform>" or typestr == "class tf2::Stamped<tf2::Transform>" or typestr == "const class tf2::Stamped<tf2::Transform>" or typestr ==  "::tf2::Stamped<tf2::Transform>_<allocator<void> >" or typestr == "operatorStamped<tf2::Transform>" or typestr =="Stamped<tf2::Transform>" or typestr == "const Stamped<tf2::Transform>" or typestr == "class Stamped<tf2::Transform>" or typestr == "const class Stamped<tf2::Transform>" or typestr ==  "::Stamped<tf2::Transform>_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorgeometry_msgs::PoseStamped" or typestr =="geometry_msgs::PoseStamped" or typestr == "const geometry_msgs::PoseStamped" or typestr == "class geometry_msgs::PoseStamped" or typestr == "const class geometry_msgs::PoseStamped" or typestr ==  "::geometry_msgs::PoseStamped_<allocator<void> >" or typestr == "operatorPoseStamped" or typestr =="PoseStamped" or typestr == "const PoseStamped" or typestr == "class PoseStamped" or typestr == "const class PoseStamped" or typestr ==  "::PoseStamped_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorgeometry_msgs::Quaternion" or typestr =="geometry_msgs::Quaternion" or typestr == "const geometry_msgs::Quaternion" or typestr == "class geometry_msgs::Quaternion" or typestr == "const class geometry_msgs::Quaternion" or typestr ==  "::geometry_msgs::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf2::Quaternion" or typestr =="tf2::Quaternion" or typestr == "const tf2::Quaternion" or typestr == "class tf2::Quaternion" or typestr == "const class tf2::Quaternion" or typestr ==  "::tf2::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf::Quaternion" or typestr =="tf::Quaternion" or typestr == "const tf::Quaternion" or typestr == "class tf::Quaternion" or typestr == "const class tf::Quaternion" or typestr ==  "::tf::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf2::Transform" or typestr =="tf2::Transform" or typestr == "const tf2::Transform" or typestr == "class tf2::Transform" or typestr == "const class tf2::Transform" or typestr ==  "::tf2::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorros::TimeBase" or typestr =="ros::TimeBase" or typestr == "const ros::TimeBase" or typestr == "class ros::TimeBase" or typestr == "const class ros::TimeBase" or typestr ==  "::ros::TimeBase_<allocator<void> >" or typestr == "operatorTimeBase" or typestr =="TimeBase" or typestr == "const TimeBase" or typestr == "class TimeBase" or typestr == "const class TimeBase" or typestr ==  "::TimeBase_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorros::Duration" or typestr =="ros::Duration" or typestr == "const ros::Duration" or typestr == "class ros::Duration" or typestr == "const class ros::Duration" or typestr ==  "::ros::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf2::Duration" or typestr =="tf2::Duration" or typestr == "const tf2::Duration" or typestr == "class tf2::Duration" or typestr == "const class tf2::Duration" or typestr ==  "::tf2::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf2::Vector3" or typestr =="tf2::Vector3" or typestr == "const tf2::Vector3" or typestr == "class tf2::Vector3" or typestr == "const class tf2::Vector3" or typestr ==  "::tf2::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortf::Vector3" or typestr =="tf::Vector3" or typestr == "const tf::Vector3" or typestr == "class tf::Vector3" or typestr == "const class tf::Vector3" or typestr ==  "::tf::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorros::Time" or typestr =="ros::Time" or typestr == "const ros::Time" or typestr == "class ros::Time" or typestr == "const class ros::Time" or typestr ==  "::ros::Time_<allocator<void> >" or typestr == "operatorTime" or typestr =="Time" or typestr == "const Time" or typestr == "class Time" or typestr == "const class Time" or typestr ==  "::Time_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatortfScalar" or typestr =="tfScalar" or typestr == "const tfScalar" or typestr == "class tfScalar" or typestr == "const class tfScalar" or typestr ==  "::tfScalar_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatordouble" or typestr =="double" or typestr == "const double" or typestr == "class double" or typestr == "const class double" or typestr ==  "::double_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operator_Bool" or typestr =="_Bool" or typestr == "const _Bool" or typestr == "class _Bool" or typestr == "const class _Bool" or typestr ==  "::_Bool_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorfloat" or typestr =="float" or typestr == "const float" or typestr == "class float" or typestr == "const class float" or typestr ==  "::float_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorbool" or typestr =="bool" or typestr == "const bool" or typestr == "class bool" or typestr == "const class bool" or typestr ==  "::bool_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
    
                    if(typestr == "operatorvoid" or typestr =="void" or typestr == "const void" or typestr == "class void" or typestr == "const class void" or typestr ==  "::void_<allocator<void> >"){
                        if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                            interp_->buffer_container(vardecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                            interp_->buffer_container(paramdecl_);
                            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
                            interp_->mkNode("REF_R4X4",(clang::Stmt*)implicitCastExpr_);
                            return;
                        }
                        else {
                            std::cout<<"Can't find declaration\n";
                            asRef->getDecl()->dump();
                        }
                    }
     
                }
            }
            this->childExprStore_ = (clang::Stmt*)implicitCastExpr_;
            interp_->mkNode("LIT_R4X4",(clang::Stmt*)implicitCastExpr_,true);
            return;
        }*/
    }

	
	arg_decay_exist_predicates["cxxBindTemporaryExpr_tf::Transform"] = [=](std::string typenm){
        if(false){ return false; }
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; }
    };
    if (cxxBindTemporaryExpr_)
    {
        ROSTFTransformMatcher exprMatcher{ context_, interp_};
        exprMatcher.setup();
        exprMatcher.visit(*cxxBindTemporaryExpr_->getSubExpr());
        this->childExprStore_ = (clang::Stmt*)exprMatcher.getChildExprStore();
        if(this->childExprStore_){return;}
    
        else{
            this->childExprStore_ = (clang::Stmt*)cxxBindTemporaryExpr_;
            interp_->mkNode("LIT_R4X4",(clang::Stmt*)cxxBindTemporaryExpr_,true);
            return;
        }
    }

	
	arg_decay_exist_predicates["materializeTemporaryExpr_tf::Transform"] = [=](std::string typenm){
        if(false){return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; }
    };
    if (materializeTemporaryExpr_)
        {
            ROSTFTransformMatcher exprMatcher{ context_, interp_};
            exprMatcher.setup();
            exprMatcher.visit(*materializeTemporaryExpr_->GetTemporaryExpr());
            this->childExprStore_ = (clang::Stmt*)exprMatcher.getChildExprStore();
        
            if(this->childExprStore_){return;}
        
            else{
                this->childExprStore_ = (clang::Stmt*)materializeTemporaryExpr_;
                interp_->mkNode("LIT_R4X4",(clang::Stmt*)materializeTemporaryExpr_,true);
                return;
            }
        }

	
	arg_decay_exist_predicates["parenExpr_tf::Transform"] = [=](std::string typenm){
        if(false){return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; } 
    };
    if (parenExpr_)
    {
        ROSTFTransformMatcher inner{ context_, interp_};
        inner.setup();
        inner.visit(*parenExpr_->getSubExpr());
        this->childExprStore_ = (clang::Stmt*)inner.getChildExprStore();
        if(this->childExprStore_){return;}
        else{
                
                std::cout<<"WARNING: Capture Escaping! Dump : \n";
                parenExpr_->dump();
           
            }
        return;
    }
	
    if (exprWithCleanups_)
        {
            ROSTFTransformMatcher exprMatcher{ context_, interp_};
            exprMatcher.setup();
            exprMatcher.visit(*exprWithCleanups_->getSubExpr());
            this->childExprStore_ = (clang::Stmt*)exprMatcher.getChildExprStore();
        
            if(this->childExprStore_){return;}
        
            else{
                this->childExprStore_ = (clang::Stmt*)exprWithCleanups_;
                interp_->mkNode("LIT_R4X4",(clang::Stmt*)exprWithCleanups_,true);
                return;
            }
        }
    
	
    if (cxxFunctionalCastExpr_)
        {
            ROSTFTransformMatcher exprMatcher{ context_, interp_};
            exprMatcher.setup();
            exprMatcher.visit(*cxxFunctionalCastExpr_->getSubExpr());
            this->childExprStore_ = (clang::Stmt*)exprMatcher.getChildExprStore();
        
            if(this->childExprStore_){return;}
        
            else{

                this->childExprStore_ = (clang::Stmt*)cxxFunctionalCastExpr_;
                interp_->mkNode("LIT_R4X4",(clang::Stmt*)cxxFunctionalCastExpr_,true);
                return;
            }
        }
    
	
    if (cxxOperatorCallExpr_){
        auto decl_ = cxxOperatorCallExpr_->getCalleeDecl();
        if(auto dc = clang::dyn_cast<clang::NamedDecl>(decl_)){
            auto name = dc->getNameAsString();
            if(name == "operator="){

                auto rhs = cxxOperatorCallExpr_->getArg(1);
                ROSTFTransformMatcher rhsMatcher{ context_, interp_};
                rhsMatcher.setup();
                rhsMatcher.visit(*rhs);
                    
                auto lhs = cxxOperatorCallExpr_->getArg(0);
                auto hasmemb = clang::dyn_cast<clang::MemberExpr>(lhs);
                if(hasmemb){
                    while(auto memb = clang::dyn_cast<clang::MemberExpr>(lhs))
                    {
                        lhs = memb->getBase();                
                    }
                    auto typestr = this->getTypeAsString(lhs,true);
                    if(auto asRef = clang::dyn_cast<clang::DeclRefExpr>(lhs)){
                
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorgeometry_msgs::PoseWithCovarianceStamped" or typestr =="geometry_msgs::PoseWithCovarianceStamped" or typestr == "const geometry_msgs::PoseWithCovarianceStamped" or typestr == "class geometry_msgs::PoseWithCovarianceStamped" or typestr == "const class geometry_msgs::PoseWithCovarianceStamped" or typestr ==  "::geometry_msgs::PoseWithCovarianceStamped_<allocator<void> >" or typestr == "operatorPoseWithCovarianceStamped" or typestr =="PoseWithCovarianceStamped" or typestr == "const PoseWithCovarianceStamped" or typestr == "class PoseWithCovarianceStamped" or typestr == "const class PoseWithCovarianceStamped" or typestr ==  "::PoseWithCovarianceStamped_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorgeometry_msgs::TransformStamped" or typestr =="geometry_msgs::TransformStamped" or typestr == "const geometry_msgs::TransformStamped" or typestr == "class geometry_msgs::TransformStamped" or typestr == "const class geometry_msgs::TransformStamped" or typestr ==  "::geometry_msgs::TransformStamped_<allocator<void> >" or typestr == "operatorTransformStamped" or typestr =="TransformStamped" or typestr == "const TransformStamped" or typestr == "class TransformStamped" or typestr == "const class TransformStamped" or typestr ==  "::TransformStamped_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,false);
                        if(typestr == "operatortf2::Stamped<tf2::Transform>" or typestr =="tf2::Stamped<tf2::Transform>" or typestr == "const tf2::Stamped<tf2::Transform>" or typestr == "class tf2::Stamped<tf2::Transform>" or typestr == "const class tf2::Stamped<tf2::Transform>" or typestr ==  "::tf2::Stamped<tf2::Transform>_<allocator<void> >" or typestr == "operatorStamped<tf2::Transform>" or typestr =="Stamped<tf2::Transform>" or typestr == "const Stamped<tf2::Transform>" or typestr == "class Stamped<tf2::Transform>" or typestr == "const class Stamped<tf2::Transform>" or typestr ==  "::Stamped<tf2::Transform>_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorgeometry_msgs::PoseStamped" or typestr =="geometry_msgs::PoseStamped" or typestr == "const geometry_msgs::PoseStamped" or typestr == "class geometry_msgs::PoseStamped" or typestr == "const class geometry_msgs::PoseStamped" or typestr ==  "::geometry_msgs::PoseStamped_<allocator<void> >" or typestr == "operatorPoseStamped" or typestr =="PoseStamped" or typestr == "const PoseStamped" or typestr == "class PoseStamped" or typestr == "const class PoseStamped" or typestr ==  "::PoseStamped_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorgeometry_msgs::Quaternion" or typestr =="geometry_msgs::Quaternion" or typestr == "const geometry_msgs::Quaternion" or typestr == "class geometry_msgs::Quaternion" or typestr == "const class geometry_msgs::Quaternion" or typestr ==  "::geometry_msgs::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorros::DurationBase" or typestr =="ros::DurationBase" or typestr == "const ros::DurationBase" or typestr == "class ros::DurationBase" or typestr == "const class ros::DurationBase" or typestr ==  "::ros::DurationBase_<allocator<void> >" or typestr == "operatorDurationBase" or typestr =="DurationBase" or typestr == "const DurationBase" or typestr == "class DurationBase" or typestr == "const class DurationBase" or typestr ==  "::DurationBase_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf2::Quaternion" or typestr =="tf2::Quaternion" or typestr == "const tf2::Quaternion" or typestr == "class tf2::Quaternion" or typestr == "const class tf2::Quaternion" or typestr ==  "::tf2::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf::Quaternion" or typestr =="tf::Quaternion" or typestr == "const tf::Quaternion" or typestr == "class tf::Quaternion" or typestr == "const class tf::Quaternion" or typestr ==  "::tf::Quaternion_<allocator<void> >" or typestr == "operatorQuaternion" or typestr =="Quaternion" or typestr == "const Quaternion" or typestr == "class Quaternion" or typestr == "const class Quaternion" or typestr ==  "::Quaternion_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf2::Transform" or typestr =="tf2::Transform" or typestr == "const tf2::Transform" or typestr == "class tf2::Transform" or typestr == "const class tf2::Transform" or typestr ==  "::tf2::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorros::TimeBase" or typestr =="ros::TimeBase" or typestr == "const ros::TimeBase" or typestr == "class ros::TimeBase" or typestr == "const class ros::TimeBase" or typestr ==  "::ros::TimeBase_<allocator<void> >" or typestr == "operatorTimeBase" or typestr =="TimeBase" or typestr == "const TimeBase" or typestr == "class TimeBase" or typestr == "const class TimeBase" or typestr ==  "::TimeBase_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorros::Duration" or typestr =="ros::Duration" or typestr == "const ros::Duration" or typestr == "class ros::Duration" or typestr == "const class ros::Duration" or typestr ==  "::ros::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf2::Duration" or typestr =="tf2::Duration" or typestr == "const tf2::Duration" or typestr == "class tf2::Duration" or typestr == "const class tf2::Duration" or typestr ==  "::tf2::Duration_<allocator<void> >" or typestr == "operatorDuration" or typestr =="Duration" or typestr == "const Duration" or typestr == "class Duration" or typestr == "const class Duration" or typestr ==  "::Duration_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf::Transform" or typestr =="tf::Transform" or typestr == "const tf::Transform" or typestr == "class tf::Transform" or typestr == "const class tf::Transform" or typestr ==  "::tf::Transform_<allocator<void> >" or typestr == "operatorTransform" or typestr =="Transform" or typestr == "const Transform" or typestr == "class Transform" or typestr == "const class Transform" or typestr ==  "::Transform_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R4X4_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf2::Vector3" or typestr =="tf2::Vector3" or typestr == "const tf2::Vector3" or typestr == "class tf2::Vector3" or typestr == "const class tf2::Vector3" or typestr ==  "::tf2::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R3",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R3_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R3",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R3_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortf::Vector3" or typestr =="tf::Vector3" or typestr == "const tf::Vector3" or typestr == "class tf::Vector3" or typestr == "const class tf::Vector3" or typestr ==  "::tf::Vector3_<allocator<void> >" or typestr == "operatorVector3" or typestr =="Vector3" or typestr == "const Vector3" or typestr == "class Vector3" or typestr == "const class Vector3" or typestr ==  "::Vector3_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R3",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R3_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R3",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R3_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorros::Time" or typestr =="ros::Time" or typestr == "const ros::Time" or typestr == "class ros::Time" or typestr == "const class ros::Time" or typestr ==  "::ros::Time_<allocator<void> >" or typestr == "operatorTime" or typestr =="Time" or typestr == "const Time" or typestr == "class Time" or typestr == "const class Time" or typestr ==  "::Time_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatortfScalar" or typestr =="tfScalar" or typestr == "const tfScalar" or typestr == "class tfScalar" or typestr == "const class tfScalar" or typestr ==  "::tfScalar_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatordouble" or typestr =="double" or typestr == "const double" or typestr == "class double" or typestr == "const class double" or typestr ==  "::double_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operator_Bool" or typestr =="_Bool" or typestr == "const _Bool" or typestr == "class _Bool" or typestr == "const class _Bool" or typestr ==  "::_Bool_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_BOOL",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_BOOL_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_BOOL",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_BOOL_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorfloat" or typestr =="float" or typestr == "const float" or typestr == "class float" or typestr == "const class float" or typestr ==  "::float_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_R1",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_R1_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorbool" or typestr =="bool" or typestr == "const bool" or typestr == "class bool" or typestr == "const class bool" or typestr ==  "::bool_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_BOOL",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_BOOL_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_BOOL",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_BOOL_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
            
                        typestr = this->getTypeAsString(lhs,true);
                        if(typestr == "operatorvoid" or typestr =="void" or typestr == "const void" or typestr == "class void" or typestr == "const class void" or typestr ==  "::void_<allocator<void> >"){
                            if(auto vardecl_ = clang::dyn_cast<clang::VarDecl>(asRef->getDecl())){
                                interp_->buffer_link(vardecl_);
                                interp_->mkNode("REF_Void",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_Void_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else if(auto paramdecl_ = clang::dyn_cast<clang::ParmVarDecl>(asRef->getDecl())){
                                interp_->buffer_link(paramdecl_);
                                interp_->mkNode("REF_Void",(clang::Stmt*)lhs);
                                interp_->buffer_operand(lhs);
                                interp_->buffer_operand(rhsMatcher.getChildExprStore());
                                
                                interp_->mkNode("ASSIGN_Void_AT_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                                this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                                return;
                            }
                            else {
                                std::cout<<"Can't find declaration\n";
                                asRef->getDecl()->dump();
                            }
                        }
             
                    }
                }
                else if(auto asRef = clang::dyn_cast<clang::DeclRefExpr>(lhs)){
                    interp_->mkNode("REF_R4X4",(clang::Stmt*)lhs);
                    interp_->buffer_operand(lhs);
                    interp_->buffer_operand(rhs);
                                
                    interp_->mkNode("ASSIGN_R4X4",(clang::Stmt*)cxxOperatorCallExpr_);
                    return;
                }
            }
        }
    }
	
    if(declRefExpr_){
        if(auto dc = clang::dyn_cast<clang::VarDecl>(declRefExpr_->getDecl())){
            interp_->buffer_link(dc);
            interp_->mkNode("REF_R4X4",declRefExpr_);
            this->childExprStore_ = (clang::Stmt*)declRefExpr_;
            return;

        }
        else if(auto dc = clang::dyn_cast<clang::ParmVarDecl>(declRefExpr_->getDecl())){
            interp_->buffer_link(dc);
            interp_->mkNode("REF_R4X4",declRefExpr_);
            this->childExprStore_ = (clang::Stmt*)declRefExpr_;
            return;

        }
    }

	
	arg_decay_exist_predicates["CXXOperatorCallExpr(tf::Transform,tf::Transform)@*@tf::Transform"] = [=](std::string typenm){
        if(false){ return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; }
    };
	arg_decay_exist_predicates["CXXOperatorCallExpr(tf::Transform,tf::Transform)@*@tf::Transform"] = [=](std::string typenm){
        if(false){ return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else { return false; }
    };
    if(cxxOperatorCallExpr_){
        auto decl_ = cxxOperatorCallExpr_->getCalleeDecl();
        if(auto dc = clang::dyn_cast<clang::NamedDecl>(decl_)){
            auto name = dc->getNameAsString();

            if(name == "operator*" or name =="*" or name == "const *" or name == "class *" or name == "const class *" or name ==  "::*_<allocator<void> >"){
                auto arg0=cxxOperatorCallExpr_->getArg(0);
                auto arg0str = this->getTypeAsString(arg0,true);

                auto arg1=cxxOperatorCallExpr_->getArg(1);
                auto arg1str = this->getTypeAsString(arg1,true);

                clang::Stmt* arg0stmt = nullptr;

                clang::Stmt* arg1stmt = nullptr;
              
                if (arg_decay_exist_predicates["CXXOperatorCallExpr(tf::Transform,tf::Transform)@*@tf::Transform"](arg0str) and 
                    arg_decay_exist_predicates["CXXOperatorCallExpr(tf::Transform,tf::Transform)@*@tf::Transform"](arg1str)){
                    if(false){}
                    else if(arg0str == "operatortf::Transform" or arg0str =="tf::Transform" or arg0str == "const tf::Transform" or arg0str == "class tf::Transform" or arg0str == "const class tf::Transform" or arg0str ==  "::tf::Transform_<allocator<void> >" or arg0str == "operatorTransform" or arg0str =="Transform" or arg0str == "const Transform" or arg0str == "class Transform" or arg0str == "const class Transform" or arg0str ==  "::Transform_<allocator<void> >"){
            
                        ROSTFTransformMatcher arg0m{this->context_,this->interp_};
                        arg0m.setup();
                        arg0m.visit(*arg0);
                        arg0stmt = arg0m.getChildExprStore();
                    }
                    if(false){}
                    else if(arg1str == "operatortf::Transform" or arg1str =="tf::Transform" or arg1str == "const tf::Transform" or arg1str == "class tf::Transform" or arg1str == "const class tf::Transform" or arg1str ==  "::tf::Transform_<allocator<void> >" or arg1str == "operatorTransform" or arg1str =="Transform" or arg1str == "const Transform" or arg1str == "class Transform" or arg1str == "const class Transform" or arg1str ==  "::Transform_<allocator<void> >"){
            
                        ROSTFTransformMatcher arg1m{this->context_,this->interp_};
                        arg1m.setup();
                        arg1m.visit(*arg1);
                        arg1stmt = arg1m.getChildExprStore();
                    }
                    if(arg0stmt and arg1stmt){
                        //interp_->mk(cxxOperatorCallExpr_,arg0stmt,arg1stmt);
                        
                        interp_->buffer_operand(arg0stmt);
                        interp_->buffer_operand(arg1stmt);
                        interp_->mkNode("MUL_R4X4_R4X4",cxxOperatorCallExpr_,true);
                        this->childExprStore_ = (clang::Stmt*)cxxOperatorCallExpr_;
                        return;
                    }
            
                }
            }
        }
    }

	
	arg_decay_exist_predicates["CXXMemberCallExpr(tf::Transform)@inverse@Capture=falsetf::Transform"] = [=](std::string typenm){
        if(false){return false;}
		else if(typenm == "operatortf::Transform" or typenm =="tf::Transform" or typenm == "const tf::Transform" or typenm == "class tf::Transform" or typenm == "const class tf::Transform" or typenm ==  "::tf::Transform_<allocator<void> >" or typenm == "operatorTransform" or typenm =="Transform" or typenm == "const Transform" or typenm == "class Transform" or typenm == "const class Transform" or typenm ==  "::Transform_<allocator<void> >"){ return true; }
        else {return false;}
    };
    if(cxxMemberCallExpr_){
        auto decl_ = cxxMemberCallExpr_->getMethodDecl();
        if(auto dc = clang::dyn_cast<clang::NamedDecl>(decl_)){
            auto name = dc->getNameAsString();
            

            if((name == "operatorinverse" or name =="inverse" or name == "const inverse" or name == "class inverse" or name == "const class inverse" or name ==  "::inverse_<allocator<void> >")){
                auto arg0 = cxxMemberCallExpr_->getImplicitObjectArgument();
                auto arg0str = this->getTypeAsString(arg0,true);
                
                clang::Stmt* arg0stmt = nullptr;
            
                if (true and arg_decay_exist_predicates["CXXMemberCallExpr(tf::Transform)@inverse@Capture=falsetf::Transform"](arg0str)){
                    if(false){}
                    else if(arg0str == "operatortf::Transform" or arg0str =="tf::Transform" or arg0str == "const tf::Transform" or arg0str == "class tf::Transform" or arg0str == "const class tf::Transform" or arg0str ==  "::tf::Transform_<allocator<void> >" or arg0str == "operatorTransform" or arg0str =="Transform" or arg0str == "const Transform" or arg0str == "class Transform" or arg0str == "const class Transform" or arg0str ==  "::Transform_<allocator<void> >"){
                        ROSTFTransformMatcher arg0m{this->context_,this->interp_};
                        arg0m.setup();
                        arg0m.visit(*arg0);
                        arg0stmt = arg0m.getChildExprStore();
                    }
                    if(true and arg0stmt){
                        //interp_->mk(cxxMemberCallExpr_,arg0stmt);
                        
                        interp_->buffer_operand(arg0stmt);
                        interp_->mkNode("INV_R4X4", cxxMemberCallExpr_,false);
                        this->childExprStore_ = (clang::Stmt*)cxxMemberCallExpr_;
                        return;
                    }
            
                }
            }
        }
    }

	
    if(cxxConstructExpr_ and cxxConstructExpr_->getNumArgs() == 0){
        if(true ){
            
            if(true ){
                //interp_->mk(cxxConstructExpr_);
                
                auto consDecl_ = cxxConstructExpr_->getConstructor();
                if(this->interp_->existsConstructor(consDecl_))
                {

                }
                else
                {
                    std::vector<const clang::ParmVarDecl*> valid_params_;
                    auto params_ = consDecl_->parameters();
                    if(params_.size() > 0){

                        
                        
                        
                        /*for(auto a:consDecl_->parameters())
                        {
                            if(auto dc = clang::dyn_cast<clang::ParmVarDecl>(a)){
                                interp_->mkNode("CONSTRUCTOR_PARAM", a,false);
                                params_.push_back(const_cast<clang::ParmVarDecl*>(a));
                             }
                            else
                            {
                                std::cout << "Warning : Param is not a ParmVarDecl\n";
                                a->dump();
                            }
                        }*/
                        if(valid_params_.size()>0)
                            interp_->buffer_operands(valid_params_);
                    }
                    interp_->mkConstructor(consDecl_);
                }

                interp_->buffer_constructor(consDecl_);
                interp_->mkNode("LIT_R4X4",cxxConstructExpr_,true);
                this->childExprStore_ = (clang::Stmt*)cxxConstructExpr_;
                return;
            }
        }
    }


};

