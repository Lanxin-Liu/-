#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__

#include "cocos2d.h"


/*@name  ��Ц��*/
/*�����࣬���ﴴ��������Ϸ������Sprite*/

//��������
enum ConstructionType{
	BASE,POWER,MINER,MILICAMP,TANKFAC,RADAR
};

class Construction : public cocos2d::Sprite 
{
public:
	/*��������*/
	static Construction* creatWithType(ConstructionType type);

	bool initWithType(ConstructionType type);

	void ConstructionDestroy(Construction * construction);

	/*����/�õ�����Ѫ��*/
	void setMaxHP(int Hp);
	int getHpNow() ;
	/*����/������Ǯ*/
	void setCostMon(int money);
	void setProMon(int money);
	int getProMon();
	/*����/������Դ*/
	void setCostPow(int power);
	void setProPow(int power);
	int getProPow();
	int getCostPow();


/***************************************��������*********************************************/
private:

	int _Max_HP;                    /*�����������*/
	int _HPNow;                      /*������ǰ����*/
	int _cost_money;             /*���컨��*/

	int _ProduceMoneyPerFrame;             /*������Ǯ��Ŀ*/

	int _cost_power;              /*���ĵ���*/

	int _produce_power;            /*��������*/



};
#endif //__CONSTRUCTION_H__
