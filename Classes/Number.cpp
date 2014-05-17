#include "Number.h"

NumberSeries::NumberSeries()
{

}

NumberSeries::~NumberSeries()
{

}

bool NumberSeries::init()
{
	number_series_ = cocos2d::Vector<SpriteFrame*>(10);
	return true;
}

void NumberSeries::loadNumber( const char* __fmt, int __base /*= 0*/ )
{
	for (int i = __base; i < 10 + __base; i++){
		const char* __filename = String::createWithFormat(__fmt, i)->getCString();
		auto __frame = AtlasLoader::getInstance()->getSpriteFrameByName(__filename);
		number_series_.pushBack(__frame);
	}
}

SpriteFrame* NumberSeries::at( int __index )
{
	return number_series_.at(__index);
}

Number* Number::inst_ = nullptr;
Number::Number()
{

}

Number::~Number()
{

}

Number* Number::getInstance()
{
	if(!inst_) 
	{
		inst_ = new Number();
		if(!inst_->init())
		{
			delete inst_;
			inst_ = NULL;
		}
	}
	return inst_;
}

void Number::destroyInstance()
{
	if(inst_)
	{
		delete inst_;
		inst_ = NULL;
	}
}

bool Number::loadNumber( const char* __name, const char* __fmt, int __base /*= 0*/ )
{
	auto __number_series = NumberSeries::create();
	__number_series->loadNumber(__fmt, __base);
	number_container_.insert(__name, __number_series);
	return true;
}

Node* Number::convert( const char* __name, int __number, Gravity gravity /*= Gravity::GRAVITY_CENTER*/ )
{
	auto __numbers = number_container_.at(__name);
	if (__numbers == 0) {
		auto __number_zero = Sprite::createWithSpriteFrame(__numbers->at(0));
		__number_zero->setAnchorPoint(Point(0.5, 0));
		return __number_zero;
	}

	auto __number_node = Node::create();
	float __total_width = 0;
	while(__number){
		int temp = __number % 10;
		__number /= 10;
		auto __sprite = Sprite::createWithSpriteFrame(__numbers->at(temp));
		__total_width += __sprite->getContentSize().width;
		__number_node->addChild(__sprite);
	}

	auto __number_zero = Sprite::createWithSpriteFrame(__numbers->at(0));
	__number_node->setContentSize(Size(__total_width, __number_zero->getContentSize().height));

	if(gravity == Gravity::GRAVITY_CENTER) {
		float single_width = __total_width/__number_node->getChildrenCount();
		int index = __number_node->getChildrenCount()/2;
		for(auto child : __number_node->getChildren()) {
			child->setAnchorPoint(Point(0.5, 0));
			float __off_length = single_width*index--;
			child->setPositionX(__off_length);
		}
	}else if(gravity == Gravity::GRAVITY_RIGHT) {
		float singleWidth = __total_width/__number_node->getChildrenCount();
		int index = __number_node->getChildrenCount();
		for(auto child : __number_node->getChildren()) {
			child->setAnchorPoint(Point(1, 0));
			float offLength = singleWidth*index--;
			child->setPositionX(offLength);
		} 
	}else if(gravity == Gravity::GRAVITY_LEFT) {
		float singleWidth = __total_width/__number_node->getChildrenCount();
		int index = 0;
		for(auto child : __number_node->getChildren()) {
			child->setAnchorPoint(Point::ZERO);
			float offLength = singleWidth*index++;
			child->setPositionX(offLength);
		} 
	}
	return __number_node;
}

bool Number::init()
{
	return true;
}


