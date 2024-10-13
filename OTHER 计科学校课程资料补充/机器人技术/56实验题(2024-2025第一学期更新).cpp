//机器人足球仿真 实验抽取考题 更新于2024-2025第一学期
//********拿球后行为，利用已有 Worldmodel（21道题）
//(1)在 playOn 模式下，拿到球以后朝前方快速带球。
soc = dribble(0.0,DRIBBLE_FAST);
//(2)在 PlayOn 模式下，拿到球以后朝球门方向慢速带球。
Angle ang = (VecPosition(52.5,0.0)-posAgent).getDirection()
soc = dribble(ang,DRIBBLE_SLOW);
//(3)在 playOn 模式下，拿到球以后把球围绕自己身体逆时针转。
soc = kickBallCloseToBody(-120);
//(4)在 playOn 模式下，拿到球后，有人逼抢(自身周围 7 米范围有至少 1 名对方球员)，则把球踢到距离对手的另外一侧，安全带球（如对手在右侧，把球踢到左侧，如对手仔左侧，把球踢到右侧）。
Circle cir(posAgent,7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(num >= 1) {
    //对手在右侧，把球踢到左侧，对手在左侧，把球踢到右侧
    Angle ang = 0;
    ObjectT opponent = WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,posAgent);//找最近的对手对象
    VecPosition position = WM->getGlobalPosition(opponent);
    if((opponent-posAgent).getDirection() >= 0) {
        ang += 45;
    } else {
        ang -= 45;
    }
    soc = dribble(ang,DRIBBLE_WITHBALL);
} else {
    //周围没逼抢的，带球到球门
    Angle ang = (VecPosition(52.5,0.0)-posAgent).getDirection()
    soc = dribble(ang,DRIBBLE_SLOW);
}
//(5)在 playOn 模式下，拿到球以后，有人逼抢，传球给最近的队友；否则向球门方向快速带球。
Circle cir(posAgent,7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(num >= 1) {
    ObjectT teammate = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent);//找最近的自己人
    soc = leadingPass(teammate,1);
} else {
    //带球到球门
    Angle ang = (VecPosition(52.5,0.0)-posAgent).getDirection()
    soc = dribble(ang,DRIBBLE_FAST);
}
//(6)在 playOn 模式下，如果有人逼抢(自身周围 7 米范围有至少 1 名对方球员)，则安全带球；否则向球门方向快速带球。
Circle cir(posAgent,7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(num >= 1) {
    soc = dribble(0.0,DRIBBLE_WITHBALL);
} else {
    //周围没逼抢的，带球到球门
    Angle ang = (VecPosition(52.5,0.0)-posAgent).getDirection()
    soc = dribble(ang,DRIBBLE_FAST);
}
//(7)在 PlayOn 模式下，若前方没有对方球员，则直接以最大速度向对方球门射门（周期数为偶数，球门的右侧射门，周期为奇数，向球门的左侧射门）。
if(WM->isOpponentAtAngle(-30,30) == false){
  VecPosition posGoal( PITCH_LENGTH/2.0,
                 (-1 + 2*(WM->getCurrentCycle()%2)) * 0.4 * SS->getGoalWidth() ); 
  soc = kickTo( posGoal, SS->getBallSpeedMax() ); 
}
//(8)在 playOn 模式下，拿到球后，在本方半场踢到球场中心点；过了半场，快速带球到对方球门。
if(WM->getBallPos().getX() < 0) {
    soc = kickTo(VecPosition(0,0),1.0);
} else {
    Angle ang = (VecPosition(52.5,0)-posAgent).getDirection();
    soc = dribble(ang,DRIBBLE_FAST);
}
//(9)在 PlayOn 模式下，拿到球后，把传给最近的周围没人防守的队友（没有人防守以其周围 5 米范围是否有对方球员为准）脚下。
Circle cir(posAgent,5);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(num == 0) {
    soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent),1.0);
} else //周围没符合条件的队友，先带球润
    soc = dribble(0,DRIBBLE_WITHBALL);
//(10) 在 playOn 模式下，拿到球后，把球传给最靠近自己的前方的没人防守的队友（判断队友身边 5 米范围是否有对方防守队员）。
Circle cir(posAgent,5);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
VecPosition closestTeammate = WM->getGlobalPosition(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent));
Angle ang = (closestTeammate - posAgent).getDirection();
if(num == 0 && ang >= -90 && ang > 90) {
    soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent),1.0);
} else //周围没符合条件的队友，先带球润
    soc = dribble(0,DRIBBLE_WITHBALL);
//(11) 在 playOn 模式下，拿到球后以后，在本方半场传给次近的队友；在对方半场，非 10 号球员传球给 10 号球员，10 号球员则快速向球门方向带球。
if(WM->getBallPos().getX() < 0)//在我们这边
  soc = leadingPass(WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,WM->getAgentObjectType()),1.0);
else {//在敌方半场
  if(WM->getPlayerNumber() != 10)
    soc = leadingPass(OBJECT_TEAMMATE_10,1.0);
  else
    soc = dribble((VecPosition(52.5,0)-posAgent).getDirection(),DRIBBLE_FAST);
}
//(12) 在 playOn 模式下，如果在本方半场，则朝前方慢速带球，如果在对方半场，则朝球门快速带球。
if(WM->getBallPos().getX() < 0)//在我们这边
  soc = dribble(0,DRIBBLE_SLOW);
else //在敌方半场
  soc = dribble((VecPosition(52.5,0)-posAgent).getDirection(),DRIBBLE_FAST);
//(13) 在 playOn 模式下，拿到球后，如果是 2 号，则把球踢到左侧边线，如果是 5 号，则把球踢到右侧边线，并把脖子方向转向球；其他球员则向前带球。
int number = WM->getPlayerNumber();
if(number == 2) {
    soc = kickTo(VecPosition(WM->getBallPos().getX(),-34),1.0);//左边线
} else if(number == 5) {
    soc = kickTo(VecPosition(WM->getBallPos().getX(),34),1.0);//右边线
} else 
    soc = dribble(0,DRIBBLE_BALL);
//(14) 在 playOn 模式下，拿到球后，如果 4 号，则传球给 7 号; 否则的话，传球给最近的队友；到对方禁区后以最大速度射向空隙大的球门一侧。
int num = WM->getPlayerNumber();
if(num == 4) {
    soc = leadingPass(OBJECT_TEAMMATE_7)
} else 
    soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent),1.0);
//到对方禁区后以最大速度射向空隙大的球门一侧
if(WM->isInTheirPenaltyArea(WM->getBallPos())) {
    //球门与我
    Angle angGoalie = (WM->getGlobalPosition(WM->getOppGoalieType())-posAgent).getDirection();
    Angle angUp = (VecPosition(52.5,6.0)-posAgent).getDirection();
    Angle angDown = (VecPosition(52.5,-6.0)-posAgent).getDirection();
    //比较空隙//取绝对值消负号
    if(std::fabs(angUp - angGoalie) > std::fabs(angDownc- angGoalie))
        soc = kickTo(VecPosition(52.5,6.0),SS->getBallSpeedMax());
    else 
        soc = kickTo(VecPosition(52.5,-6.0),SS->getBallSpeedMax());
}
//(15) 在 playOn 模式下，拿球后垂直带球。
if(WM->getBallPos().getY() <= 0)
    soc = dribble(90,DRIBBLE_WITHBALL);
else
    soc = dribble(-90,DRIBBLE_WITHBALL);
//(16) 在 playOn 模式下，拿到球后带球到达球场中心；在球场中心附近位置（中心位置周围 2 米半径范围内）传给最近的球员。
if(posAgent.getDistanceTo(posBall) > 2) //带球去中心(0,0)
    soc = dribble((VecPosition(0,0)-posAgent).getDirection(),DRIBBLE_WITHBALL);
else //在2m范围内，即中心
    soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent),1.0);
//(17) 在 playOn 模式下，如果 10 号控球，则其带球前进，然后 5 号跟着 10号一起前进，两球员在同一水平线上，且距离为 5。
int number = WM->getPlayerNumber();
if(number == 10) {
    soc = dribble(0,DRIBBLE_WITHBALL);
} else if(number == 5) {
    //水平差5
    VecPosition pos(WM->getBallPos().getX()-5,WM->getBallPos().getY());
    soc = moveToPos(pos,20);
}
//(18) 在 playon 模式下，如果是 10 号球员，在可踢球的状态下，如果自身的x 轴坐标大于 30，则直接朝着离对方球员远的球门点射门。
if(WM->getPlayerNumber() == 10 && posAgent.getX() > 30) 
    soc=kickTo(VecPosition(52.5,0),PS->getPlayerWhenToTurnAngle());
else 
    soc=leadingPass(OBJECT_TEAMMATE_10,1.0);
//(19) 在 playOn 模式下，如果是 9 号拿到球，则令 9 号和 10 号同时冲至敌方球门处，在球门前，9 号传给 10 号，由 10 号进行射门
//不同于getPlayerNumber，此方法getAgentObjectType是获取谁拿到了球
AngDeg ang = (VecPositoin(52.5,0)-posAgent).getDirection();
if(WM->getAgentObjectType() != OBJECT_TEANMATE_9) {
    //向9号传球，让9号拿到球
    soc = leadingPass(OBJECT_TEAMMATE_9,1.0);
    soc = dribble(ang,DRIBBLE_FAST);
} else {
    // 9号传球给10号
    soc = leadingPass(OBJECT_TEAMMATE_10,1.0);
    if (WM->getAgentObjectType() == OBJECT_TEAMMATE_10) // 10号球员拿到球，射门
        soc = kickTo(ang, KICK_STRONG);
}
//(20) 在 playOn 模式下，如果我是 4 号球员并且拿到了球，则传给 7 号球员，同时 7 号球员再传给 9 号球员，9 号球员继续以最大速度冲到球门处射门。
if(WM->getPlayerNumber() == 4 && WM->isBallKickable()) {
    soc = leadingPass(OBJECT_TEAMMATE_7,1);
} else if(WM->getPlayerNumber() == 7 && WM->isBallKickable()) {
    soc = leadingPass(OBJECT_TEAMMATE_9,1);
} else if(WM->getPlayerNumber() == 9) {
    if(WM->getBallPos().getX() < 40) 
        soc = dribble(VecPositoin(40,0)-posAgent).getDirection(),DRIBBLE_FAST);
    else 
        soc = ShootToGoalex(OBJECT_GOAL_L);
}
//(21) 在 playOn 模式下，如果在我方半场拿到球，则向中场线以最大的速度踢，如果在敌方半场拿到球，则向敌方球门处以最大的速度踢
if(WM->getBallPos().getX() <= 0) {
    VecPosition pos(0,WM->grtBallPos().getY());
    soc = kickTo(pos,SS->getBallSpeedMax());
} else 
    soc = kickTo(VecPosition(52.5,0),SS->getBallSpeedMax());
//********拿球以后，需要自己添加 WorldModel 函数（12道题）
//(22) 在 playOn 模式下，拿球后传球给更靠近对方球门的最近队友。
soc = leadPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,WM->getPosOpponentGoal()),1.0);
//(23) 在 playOn 模式下，拿球后，搜索前方-30~30 之间距离自己 20 米内是否有队友，如果有则传给该队友，否则自己带球。
//在WorldModel.h头文件预定义函数
//判断当前球员角度在angA~angB之间距离小于dDist范围内是否有队友球员
std::vector<ObjectT> getTeammatesInAngleRange(AngDeg angA,AngDeg angB,double dDist);
//在WorldModel.c里定义函数体
std::vector<ObjectT>::getTeammatesInAngleRange(AngDeg angA,AngDeg angB,double dDist) {
    VecPosition posAgent = getAgentGlobalPosition();
    std::vector<ObjectT> teammatesInRange;
    VecPosition posOpp;
    AngDeg angOpp;
    int iIndex;
    for(
        ObjectT o = iterateObjectStart(iIndex,OBJECT_SET_TEAMMATES);
        o != OBJECT_ILLEGAL;
        o = iterateObjectNext(iIndex,OBJECT_SET_TEAMMATES)) {
            posOpp = getGlobalPosition(o);
            angOpp = (posOpp - posAgent).getDirection();
            //角度之内 距离之内
            if(angA <= angOpp && angOpp <= angB && posAgent.getDistanceTo(posOpp) < dDist) {
                teammatesInRange.push_back(o);
            }
        }
    iterateObjectDone(iIndex);
    return teammatesInRange;   
}
//在球可踢那里添加如下
double ang = (VecPosition(52.5,0)-posAgent).getDirection();
auto teammatesInRange = WM->getTeammatesInAngleRange(ang-30,ang+30,20);
if (!teammatesInRange.empty()) {
    // 如果不为空说明视角范围内有队友，传球
    ObjectT closestTeammate = teammatesInRange[0];
    soc = leadingPass(closestTeammate, 1.0);
} else 
    soc = dribble(ang, DRIBBLE_WITHBALL);
//(24) 在 playon 模式下，求出 y 轴等于 0 的两侧的对方球员数量，将球传向对手少的一方，并且 x 轴值最大的队友。
//在WorldModel.h头文件预定义函数
bool isOwnSideOpponentMost();
ObjectT getMaxXTeammateInSide(bool isOwnSize);
//在WorldModel.c里定义函数体
//求出y轴等于0的两侧的对方球员数量，返回对手少并且x轴值最大的队友。
ObjectT WorldModel::getMaxXTeammateInSide(bool isOwnSize) {
    int iIndex;
    ObjectT maxMate = OBJECT_ILLEGAL;
    for(
        ObjectT o = iterateObjectStart(iIndex, OBJECT_SET_TEAMMATES);
        o != OBJECT_ILLEGAL;
        o = iterateObjectNext(iIndex, OBJECT_SET_TEAMMATES)) {
            VecPosition oPos = getGlobalPosition(o);
            if(
                (isOwnSize && oPos.getY() >= 0) || 
                (!isOwnSize && oPos.getY() <= 0)) {
                    //如果存在x值更大的，更新maxMate
                    if(
                        maxMate == OBJECT_ILLEGAL || 
                        oPos.getX() > getGlobalPosition(maxMate).getX()) {
                            maxMate = o;
                        }
            }
        }
    iterateObjectDone(iIndex);
    return maxMate;
}
//判断哪边对手少，true代表我方对手少
bool WorldModel::isOwnSideOpponentMost() {
    int ownSideCount = 0;
	int count = 0;  
    int iIndex;
    ObjectT maxMate = OBJECT_ILLEGAL;
    for (
        ObjectT o = iterateObjectStart(iIndex, OBJECT_SET_OPPONENTS);
        o != OBJECT_ILLEGAL;
        o = iterateObjectNext(iIndex, OBJECT_SET_OPPONENTS)) {
            if (getGlobalPosition(o).getY() > 0)
                ownSideCount++;
            count++;
            }
	return ownSideCount > count - ownSideCount;
}
//在球可踢那里添加如下
ObjectT mate = WM->getMaxXTeammateInSide(!WM->isOwnSideOpponentMost());
soc = leadingPass(mate,1,DIR_CENTER);
//(25) 在 playon 模式下，如果自身 7 米范围内有两个或两个以上的对手的话，则传球到 x 轴值最大的队友。
//在WorldModel.h头文件预定义函数
ObjectT getMaxXTeammate();
//在WorldModel.c里定义函数体
ObjectT WorldModel::getMaxXTeammate() {
    int iIndex;
    ObjectT maxMate = OBJECT_ILLEGAL;
    for (
        ObjectT  o = iterateObjectStart(iIndex, OBJECT_SET_TEAMMATES);
        o != OBJECT_ILLEGAL;
        o = iterateObjectNext(iIndex, OBJECT_SET_TEAMMATES)) {
            VecPosition oPos = getGlobalPosition(o);
            if (
                maxMate == OBJECT_ILLEGAL || 
                oPos.getX() > getGlobalPosition(maxMate).getX()) {
                    maxMate = o;
                }
    }
    iterateObjectDone(iIndex);
    return maxMate;
}
//在球可踢那里添加如下
Circle cir(WM->getAgentGlobalPosition(),7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if (num > 2) {
    ObjectT mate = WM->getMaxXTeammate();
    soc = leadingPass(mate,1,DIR_CENTER);
} else 
	soc = dribble((WM->getPosOpponentGoal() - WM->getAgentGlobalPosition()).getDirection(), DRIBBLE_FAST);
//(26) 在 playon 模式下，求出己方的越位线，存在可以踢球的队友的话，如果自身是 10 号。那么 10 球员垂直跑向越位线的 x 轴值-2 米，y 轴不变的点。
if(WM->isBallInOurPossesion() && WM->getPlayerNumber == 10)
    soc = moveToPos(WM->getOffsideX()-2,posAgent.getY(),20);
//(27) 在 playon 的模式下，求出球运动方向（即求出其对应的直线方程），并且求出自己到该直线的距离，如果距离小于 4 的话，那么就垂直跑向该条直线。
/*找到代码：
formations->setFormation( FT_433_OFFENSIVE );//设置球队出场阵形！
soc.commandType = CMD_ILLEGAL;//初始化soc命令对象
在该代码后加入*/
Line ballRun = Line::makeLineFromPositionAndAngle(WM->getBallPos(),WM->getBallDirection());
if (ballRun.getDistanceWithPoint(WM->getAgentGlobalPosition()) < 4) {
    soc = moveToPos(ballRun.getPointOnLineClosestTo(WM->getAgentGlobalPosition()),20);
    ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue( turnNeckToObject(OBJECT_BALL,soc));
    return soc;
}
//(28) 在 playon 的模式下，如果是自己可以踢球的状态下，如果自身 7 米内没有对方球员的话，则快速带球，带球方向是朝着点（53,0）方向。
Circle cir(posAgent,7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(num >= 1) {
    soc = dribble(0.0,DRIBBLE_WITHBALL);
} else {
    //周围没逼抢的，带球到球门
    Angle ang = (VecPosition(53,0)-posAgent).getDirection()
    soc = dribble(ang,DRIBBLE_FAST);
}
//(29) 在 playon 的模式下，如果距离球最近的是我方队友的话，如果我的 x坐标小于 30 的话，并且我是 10 号，那么我跑向球的坐标加上（0,10）的坐标位置。
if(
    WM->isBallInOurPossesion() && 
    WM->getPlayerNumber == 10 && 
    posAgent.getX() < 30) {
        VecPosition pos = WM->getBallPos() + VecPosition(0,10);
        soc = moveToPos(pos,20);
}
//(30) 在 playon 的模式下，发现前方没有队友的时候，如果自身 5 米内有两个及两个以上的对手的话，那么将球传给最近的队友。
//在WorldModel.h头文件预定义函数
//判断当前球员角度在angA~angB之间距离小于dDist范围内是否有队友球员
bool isTeammatesInAngleRange(AngDeg angA,AngDeg angB);
//在WorldModel.c里定义函数体
bool WorldModel::isTeammatesInAngleRange(AngDeg angA,AngDeg angB) {
    VecPosition posAgent = getAgentGlobalPosition();
    VecPosition posOpp;
    AngDeg angOpp;
    int iIndex;
    for(
        ObjectT o = iterateObjectStart(iIndex,OBJECT_SET_TEAMMATES);
        o != OBJECT_ILLEGAL;
        o = iterateObjectNext(iIndex,OBJECT_SET_TEAMMATES)) {
            posOpp = getGlobalPosition(o);
            angOpp = (posOpp - posAgent).getDirection();
            //角度之内
            if(angA <= angOpp && angOpp <= angB) {
                return true;
            }
        }
    iterateObjectDone(iIndex);
    return false; 
}
//在球可踢那里添加如下
Circle cir(posAgent,7);
int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir);
if(!WM->isTeammatesInAngleRange(-30,30) && num >= 2)
    leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,posAgent),1.0);
//(31) 在 playon 的模式下，发现前方没有对方球员的时候，则快速向球门方向带球，距离守门员 5-10 米时向空隙较大的一侧射门。
if(!WM->isOpponentAtAngle(-30,30)){
    double dis = posAgent.getDistanceTo(WM->getGlobalPosition(WM->getOppGoalieType()));//距离守门员距离
    if(dis >= 5 && dis <= 10) {
        //球门与我
        Angle angGoalie = (WM->getGlobalPosition(WM->getOppGoalieType())-posAgent).getDirection();
        Angle angUp = (VecPosition(52.5,6.0)-posAgent).getDirection();
        Angle angDown = (VecPosition(52.5,-6.0)-posAgent).getDirection();
        //比较空隙//取绝对值消负号
        if(std::fabs(angUp - angGoalie) > std::fabs(angDownc- angGoalie))
            soc = kickTo(VecPosition(52.5,6.0),SS->getBallSpeedMax());
        else 
            soc = kickTo(VecPosition(52.5,-6.0),SS->getBallSpeedMax());
    } else 
        soc = dribble((VecPosition(52.5,0) - posAgent).getDirection(),DRIBBLE_FAST);
}

//********其他比赛模式下，进攻行为（8道题）
//(34) 在本方角球模式下，如果自己是 10 号球员，则跑向角球点，并开球（球可踢，则踢球给 9 号）；如果自己是 9 号球员，则跑向距离角球点附近（随机选一点），准备接应球，其他球员跑本位点.
else if (WM->isCornerKickUs()) {
///////////补充代码////////////////////////////////////////////
    if(WM->getAgentObjectType() == OBJECT_TEAMMATE_10) {
        if (WM->isBallKickable())
            soc = leadingPass(OBJECT_TEAMMATE_9, 1);
        else //跑向角球点
            soc = moveToPos(WM->getBallPos(), PS->getPlayerWhenToTurnAngle());
    } else if(WM->getAgentObjectType() == OBJECT_TEAMMATE_9) {
        VecPosition  ball = WM->getBallPos();
        VecPosition  pos(
            -(ball.getX())/fabs(ball.getX()) * 5 + ball.getX(),
            -(ball.getY())/fabs(ball.getY()) * 5 + ball.getY());
        soc = moveToPos(pos, PS->getPlayerWhenToTurnAngle());
    } else //其他球员跑本位点
        soc = moveToPos(WM->getHomePosition(), PS->getPlayerWhenToTurnAngle());
///////////补充代码//////////////////////////////////////////////
   ACT->putCommandInQueue( soc );
   ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
}
//(35) 在本方界外球模式下，如果自己是距离球最近的队员，跑向球；并开球（球可踢，则把球传给最近的队友）。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    if(WM->getFastestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL,&iTmp) == WM->getAgentObjectType()) {
        if(WM->isBallKickable()) {
           ObjectT objTea = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,WM->getAgentObjectType(),&dist);
           VecPosition posTea = WM->getGlobalPosition(objTea);
           soc = kickTo(posTea,SS->getBallSpeedMax());
        } else 
            soc = moveToPos(WM->getBallPos(),20);
        ACT->putCommandInQueue(soc);
    }
///////////补充代码//////////////////////////////////////////////
}
//(33) 在 playon 的模式下，（8，9，10，11）前方没有对方球员的时候，则快速向球门方向带球，距离守门员 5-10 米时向空隙较大的一侧射门。向球门方向带球，其他球员就将球传给7号。 
int num = getPlayerNumber();
if(num == 8 || num == 9 || num == 10 || num == 11) {
    if(WM->isOpponentAtAngle(-30,30) == false) {
        double dis = posAgent.getDistanceTo(WM->getGlobalPosition(WM->getOppGoalieType()));//距离守门员距离
        if(dis >= 5 && dis <= 10) {
            //球门与我
            Angle angGoalie = (WM->getGlobalPosition(WM->getOppGoalieType())-posAgent).getDirection();
            Angle angUp = (VecPosition(52.5,6.0)-posAgent).getDirection();
            Angle angDown = (VecPosition(52.5,-6.0)-posAgent).getDirection();
            //比较空隙//取绝对值消负号
            if(std::fabs(angUp - angGoalie) > std::fabs(angDownc- angGoalie))
                soc = kickTo(VecPosition(52.5,6.0),SS->getBallSpeedMax());
            else 
                soc = kickTo(VecPosition(52.5,-6.0),SS->getBallSpeedMax());
        } else 
            soc = dribble((VecPosition(52.5,0) - posAgent).getDirection(),DRIBBLE_FAST);
    }
} else {
    soc = leadingPass(OBJECT_TEAMMATE_7,1.0);
}
//(32) 在 playon 的模式下，如果在对方禁区内就射门，否则，如果是7号球员就向球门方向带球，其他球员就将球传给7号。
//到对方禁区
if(WM->isInTheirPenaltyArea(WM->getBallPos())) 
    soc = kickTo(VecPosition(52.5,0),1.0);
else {
    if(WM->getPlayerNumber() == 7) 
        soc = dribble(VecPosition(52.5,0),DRIBBLE_WITHBALL);
    else 
        soc = leadingPass(OBJECT_TEAMMATE_7,1.0);
}
//(36) 在本方界外球模式下，在本方半场左侧，则由 2 号去发；如果是本方半场右侧，则由 5 号去发；球在 2 号或者 5 号脚下，则踢向距离自己最近的队友。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    VecPosition posBall = WM->getBallPos();
    if(
        (posBall.getX() < 0 && posBall.getY() < 0 && WM->getPlayerNumber() == 2) ||
        ((posBall.getX() <0 && posBall.getY() > 0 && WM->getPlayerNumber() == 5))) {
        if(WM->isBallKickable()) {
            ObjectT o = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,WM->getAgentObjectType(),&dist);
            soc = kickTo(WM->getGlobalPosition(o),SS->getBallSpeedMax());
        } else
            soc = moveToPos(posBall,20); 
        ACT->putCommandInQueue(soc);
    }
///////////补充代码//////////////////////////////////////////////
}
//(37) 在本方界外球的模式下，如果我是距离球第二近的队友的话，那么我也朝着球的位置跑，直到距离球 7 米的范围。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    double myPosX = WM->getAgentGlobalPosition().getX();;
    double myposY = WM->getAgentGlobalPosition().getY();;
    double ballPosX = WM->getBallPos().getX();;
    double ballPosY = WM->getBallPos().getY();;
    //勾股定理
    double dis = sqrt(pow(ballPosX-myPosX,2)+pow(ballPosY-myPosY,2));
    if(WM->getAgentObjectType() == WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL) && dis > 7) {
        soc = moveToPos(VecPosition(ballposx,ballposy),20);
        ACT->putCommandInQueue(soc);
    }
///////////补充代码//////////////////////////////////////////////
}
//(38) 在本方界外球的模式下，如果我是 4 号的话，并且距离球最近的队友不是我，那么我将跑向球的坐标加上（5,0）的位置上去。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    if(WM->getPlayerNumber() == 4 && WM-> getClosestInSetTo( OBJECT_SET_TEAMMATES, OBJECT_BALL) != OBJECT_TEAMMATE_4)
        soc = moveToPos(WM->getBallPos() + VecPosition(5,0),20);
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); // 放入命令队列
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
}
//(39) 在本方界外球的模式下，如果我是距离球第二近的队友，那么我跑向距离球 12 米的范围内，并且距离对方球门点（52.5,0）最近的点。
else if (WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    if (WM->getAgentObjectType() == WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL)) {
        ///球
        double ballPosX = WM->getBallPos().getX();
	    double ballPosY = WM->getBallPos().getY();
        //球门
        double goalPosX = 52,5,goalPosY = 0;
        //斜率 (52.5,0)与(ballPosX,ballPosY)
	    double k = (goalPosY - ballPosY) / (goalPosX - ballPosX);
        //截距
	    double b = ballPosY - k * ballPosX;
        //计算离球12米的两个点(x1, y1) (x2, y2)
        double dx = 12 / sqrt(1 + k*k);
        double x1 = ballPosX + dx;
        double y1 = k*x1 + b;
        double x2 = ballPosX - dx;
        double y2 = k*x2 + b;
        //找最近的点
        //计算距离sqrt(x^2+y^2)
        double dis1 = sqrt(pow(goalPosX - x1, 2) + pow(goalPosY - y1, 2));
        double dis2 = sqrt(pow(goalPosX - x2, 2) + pow(goalPosY - y2, 2));
        if(dis1 < dis2) {
           soc = moveToPos(VecPosition(x1,y1),20);
        } else {
           soc = moveToPos(VecPosition(x2,y2),20);
        }
    }
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); // 放入命令队列
}
//(40) 在本方界外球的模式下，距离球最近的队友跑向球并开球，如果我不是距离球第二近的队友，那么我向球的坐标方向跑去。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    ObjectT cloestTeammate = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL);
    ObjectT secondCloestTeammate = WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL);
    if (WM->getAgentObjectType() == cloestTeammate) {
        if(WM->getGlobalPosition(cloestTeammate) != WM->getBallPos())
            soc = moveToPos(WM->getBallPos(),20);//跑向球
        else
            soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,cloestTeammate),1.0);//把球传给最近的队友,即开球
    }
    if(
        WM->getAgentObjectType() != cloestTeammate &&
        WM->getAgentObjectType() != secondCloestTeammate
        )
            soc = moveToPos(WM->getBallPos(),20);
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); 
}
//(41) 在本方界外球的模式下，距离球最近的队友跑向球并开球。如果我不是距离球第二近的队友，那么求出距离球第二近的队友的坐标加上（10，5）的点；如果该点在球场内，则跑向该点，如果该点在场外，则计算距离该点最近的边界点。
else if(WM->isOffsideUs()) {
///////////补充代码//////////////////////////////////////////////
    ObjectT cloestTeammate = WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL);
    ObjectT secondCloestTeammate = WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL);
    double secondCloestTeammatePosX = WM->getGlobalPosition(secondCloestTeammate).getX();
    double secondCloestTeammatePosY = WM->getGlobalPosition(secondCloestTeammate).getY();
    //第二近的队友在球场内
    bool isInSide = (secondCloestTeammatePosX <= 52.5 && secondCloestTeammatePosY <= 34);
    //离球最近的队友
    if (WM->getAgentObjectType() == cloestTeammate) {
        if(WM->getGlobalPosition(cloestTeammate) != WM->getBallPos())
            soc = moveToPos(WM->getBallPos(),20);//跑向球
        else
            soc = leadingPass(WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,cloestTeammate),1);//把球传给最近的队友
    }
    if(
        WM->getAgentObjectType() != cloestTeammate &&
        WM->getAgentObjectType() != secondCloestTeammate &&
        isInSide
        ) //如果不是最近也不是第二近的，并且第二近的队友在球场内
            soc = moveToPos(VecPosition(secondCloestTeammatePosX+10,secondCloestTeammatePosY+5),20);
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); 
}
//********playOn 模式下，防守行为（8道题）
//(42) 在 playOn 模式下，5 号球员与拿球的对方球员的距离始终为 5。
if(WM->getPlayerNumber() == 5) {
    VecPosition pos(WM->getBallPos().getX()-5,WM->getBallPos().getY());
    soc = moveToPos(pos,20);
}
//(43) 在 playOn 模式下，2 号和 4 号一起去盯防对方拿球队员。
if(WM->getAgentObjectType() == OBJECT_TEAMMATE_2){
    VecPosition pos(WM->getBallPos().getX()-4,WM->getBallPos().getY())
    soc = moveToPos(pos,20);
}

if(WM->getAgentObjectType() == OBJECT_TEAMMATE_4) {
    VecPosition pos(WM->getBallPos().getX(),WM->getBallPos().getY()-4)
    soc = moveToPos(pos,20);
}
//(44) 在 playOn 模式下，如果对方 10 号拿球，如果我是 2、3、4 号，则去盯防 10 号。
int num = WM->getPlayerNumber();
if(
    WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getBallPos()) == OBJECT_OPPONENT_10 &&
    (num == 2 || num == 3 || num == 4)) {
        //盯防函数
        VecPosition pos = WM->getMarkingPosition(OBJECT_OPPONENT_10,2.0,MARK_BALL);
        soc = moveToPos(pos,PS->getPlayerWhenToTurnAngle());
}
//(45) 在 playOn 模式下，如对方 9 号拿球，我方 2、3、4 号距离球最近的球员去盯防 9 号，其他队员盯防距离自己最近的对方球员
if(WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getBallPos()) == OBJECT_OPPONENT_9) {
    //初始化 我方 2、3、4 号距离球最近的球员 为2号，后续根据计算更改
    ObjectT closestObject = OBJECT_TEAMMATE_2;
    VecPosition team = WM->getGlobalPosition(closestObject);
    double minDis = team.getDistanceTo(WM->getGlobalPosition(OBJECT_OPPONENT_9));
  
    team = WM->getGlobalPosition(OBJECT_TEAMMATE_3);
    double dis = team.getDistanceTo(WM->getGlobalPosition(OBJECT_OPPONENT_9));
    if(dis < minDis) {
        minDis = dis;
        closestObject = OBJECT_TEAMMATE_3;
    }

    team = WM->getGlobalPosition(OBJECT_TEAMMATE_4);
    dis = team.getDistanceTo(WM->getGlobalPosition(OBJECT_OPPONENT_9));
    if(dis < minDis) { 
        closestObject = OBJECT_TEAMMATE_4;
    }
    //现在经过比较遍历，得到的是2 3 4离球最近的那个人及其距离
    if(WM->getAgentObjectType() == closestObject) {
        VecPosition pos = WM->getMarkingPosition(OBJECT_OPPONENT_9,2.0,MARK_BALL);
        soc = moveToPos(pos,PS->getPlayerWhenToTurnAngle());
    } else { //其他人盯防最近的球员
        ObjectT opp = WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getAgentObjectType());
        VecPosition oppPos = WM->getMarkingPosition(opp,2.0,MARK_BALL);
        soc=moveToPos(oppPos,40);
    }
}
//(46) 在 playOn 模式下，如果对方比我先接近球，则离球最近的队员去盯球，其他球员盯防距离自己最近的对方球员。
//对手
ObjectT opp = getFastestInSetTo(OBJECT_SET_OPPONENTS,OBJECT_BALL);
//对手与球距离
double oppDisToBall = getGlobalPosition(opp).getDistanceTo(getBallPos());
//队友
ObjectT teammate = getFastestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL);
//队友与球距离
double teammateDisToBall = getGlobalPosition(teammate).getDistanceTo(getBallPos());
//比较两方谁更近
if(oppDisToBall < teammateDisToBall) {
    ObjectT colestTeammate = WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getBallPos());
    if(WM->getAgentObjectType() == colestTeammate) //离球最近的盯球去
        soc = moveToPos(WM->getGlobalPosition(colestTeammate),20); 
    else { //其他球员盯防距离自己最近的对方球员
        ObjectT cloestOpponent = WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getAgentObjectType());
        //盯防函数
        VecPosition oppPos = WM->getMarkingPosition(cloestOpponent,2.0,MARK_BALL);
        soc = moveToPos(oppPos,PS->getPlayerWhenToTurnAngle()); 
    }
}
//(47) 在 playOn 模式下，如果对方 11 号拿到球，则 7 号球员从左边去断球，8号球员从右边去断球。
if(WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getBallPos()) == OBJECT_OPPONENT_11) {
    VecPosition oppPos = WM->getGlobalPosition(OBJECT_OPPONENT_11);
    //从左边去断球
    if(WM->getAgentObjectType() == 7) {
        if(WM->getGlobalPosition(OBJECT_TEAMMATE_7).getDistanceTo(oppPos) > 5)
            soc = moveToPos(VecPosition(oppPos.getX()-4,oppPos.getY()),20);//距离对手有一定距离，先移动到队友左侧(X-4)
        else
            soc = intercept(0);//在对手身边，断球
    } else if(WM->getAgentObjectType() == 8) { //从右边去断球
        if(WM->getGlobalPosition(OBJECT_TEAMMATE_8).getDistanceTo(oppPos) > 5)
            soc = moveToPos(VecPosition(oppPos.getX()+4,oppPos.getY()),20);//同理，右侧(X+4)
        else
            soc = intercept(0);
    }
}
//(48) 在 playOn 模式下，防守模式下（即球不在我方球员脚下），我方 6 号球员始终跟着敌方 9 号，我方 7 号始终跟着敌方 10 号，8 号球员始终跟着敌方11 号球员。
if(!WM->isBallInOurPossesion()) {
    if(WM->getAgentObjectType() == OBJECT_TEAMMATE_6) 
        soc = moveToPos(WM->getGlobalPosition(OBJECT_OPPONENT_9),20);
    else if(WM->getAgentObjectType() == OBJECT_TEAMMATE_7) 
        soc=moveToPos(WM->getGlobalPosition(OBJECT_OPPONENT_10),20);
    else if(WM->getAgentObjectType() == OBJECT_TEAMMATE_8) 
        soc=moveToPos(WM->getGlobalPosition(OBJECT_OPPONENT_11),20);
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); // 放入命令队列
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
}
//(49) 在 playOn 模式下，防守模式下（即球不在我方球员脚下），我方距离球最近的 2 名队员负责去盯防对方离球最近的球员，其他球员其他球员采用人球都盯的方式盯防防距离自己最近的对方球员（即跑到距离自己最近的对方球员的可能接球路线的前面位置点）

//********其他比赛模式下，防守行为（7道题）
//(50) 在对方界外球的模式下，如果我是 4 号，那么我就跑向距离球最近的对方球员处。

//(51) 在对方界外球的模式下，如果我是距离球第二近的队员的话，那么我跑向距离球第二近的对方球员的位置。
else if(WM->isOffSideThem()) {
///////////补充代码//////////////////////////////////////////////
    if(WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL) == WM->getAgentObjectType())
	    soc = moveToPos(
            WM->getGlobalPosition(WM->getSecondClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL)),
            PS->getPlayerWhenToTurnAngle());
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc );
}
//(52) 在对方角球模式情况下，如果球在我方左侧，则 2，3，6，7 号平均分布在以球的位置为圆心，半径 10 米的圆弧上（其中 2 号的初始位置可以自行设定，间距也可以自行设定，但是需要保证 2，3，6，7 都在场内）；
//如果球在我方右侧，则 4，5，7，8 号平均分布在以球的位置为圆心，半径 10 米的圆弧上（其中 4 号的初始位置可以自行设定，间距也可以自行设定，但是需要保证 4，5，7，8 都在场内）。
if(WM->isCornerKickThem()){
///////////补充代码//////////////////////////////////////////////
/*
 我方 敌方
    |     左侧
----|----> x
    |     右侧
   \/
    y
*/
    int num = WM->getPlayerNumber();
    double ballPosX = WM->getBallPos().getX();
    double ballPosY = WM->getBallPos().getY();
    //以10半径，圆心为球坐标 分布
    double radius = 10.0;
    double centerX = ballX;
    double centerY = ballY;
    if(ballPosY < 0 && ballPosX < 0) {
        if (num == 2) 
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4),centerY + radius*sin(M_PI/4)),40);
        else if (num == 3) 
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*3),centerY + radius*sin(M_PI/4*3)),40);
        else if (num == 6) 
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*5),centerY + radius*sin(M_PI/4*5)),40);
        else if (num == 7) 
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*7),centerY + radius*sin(M_PI/4*7)),40);
    } else if(ballPosY > 0 && ballPosX < 0) {
        if (num == 4)
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4),centerY + radius*sin(M_PI/4)),40);
        else if (num == 5)
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*3),centerY + radius*sin(M_PI/4*3))40);
        else if (num == 7)
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*5),centerY + radius*sin(M_PI/4*5))40);
        else if (num == 8) 
            soc = moveToPos(VecPosition(centerX + radius*cos(M_PI/4*7),centerY + radius*sin(M_PI/4*7))40);  
    }
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); // 放入命令队列
    ACT->putCommandInQueue ( turnBodyToObject ( OBJECT_BALL ) );
    //ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) ); // 把脖子转向球，也就是一直看着球
}
//(53) 在对方界外球的模式下，如果我不是距离球最近的队友，并且我的 x 轴坐标大于 0 的话，那么我跑向自身位置加（-10,0）的点的位置去。
else if(WM->isOffSideThem()) {
///////////补充代码//////////////////////////////////////////////
    if(
        WM->getClosestInSetTo(OBJECT_SET_TEAMMATES,OBJECT_BALL) != WM->getAgentObjectType() &&
        WM->getAgentGlobalPosition().getX() > 0)
            soc = moveToPos(VecPosition(-10,0) + WM->getAgentGlobalPosition(),20);
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc );
}
//(54) 在对方界外球的模式下，如果我身边 5 米内有对方球员的话，那么我跑向身边对方球员的位置，并且我的 x 轴坐标的值要比该对方的大 2。
else if(WM->isOffsideThem()) {
///////////补充代码//////////////////////////////////////////////
    Circle cir (posAgent,5) ;
    int num = WM->getNrInSetInCircle(OBJECT_SET_OPPONENTS,cir) ;
    if(num != 0) {
	    VecPosition pos = WM->getGlobalPosition(WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,posAgent)) ;
	    soc = moveToPos(pos + VecPosition(2,0),20) ;
    }
///////////补充代码//////////////////////////////////////////////
    ACT->putCommandInQueue( soc ); 
}
//(55) 在对方界外球的模式下，如果球的位置的 x 轴小于 0，如果我是 4 号或 5号的话，一起跑向距离球第二近的对方球员的位置。
else if(WM->isOffsideThem()) {
///////////补充代码//////////////////////////////////////////////
  if(
    (WM->getPlayerNumber() == 4 || WM->getPlayerNumber()==5) &&
    WM->getBallPos().getX() < 0
  )
	soc = moveToPos(WM->getGlobalPosition(WM->getSecondClosestInSetTo(OBJECT_SET_OPPONENTS,OBJECT_BALL)),20);
///////////补充代码//////////////////////////////////////////////
}
//(56) 在对方角球模式情况下，如果球在我方左侧，则 2，3 号负责盯防对方距离球第二近的对方球员；如果球在我方右侧，则 4，5 号负责盯防对方距离球第二近的对方球员。
else if(WM->isOffsideThem()) {
///////////补充代码//////////////////////////////////////////////
    ObjectT secondCloestOpponent = WM->getClosestInSetTo(OBJECT_SET_OPPONENTS,WM->getAgentObjectType());
    VecPosition oppPos = WM->getMarkingPosition(secondCloestOpponent,2.0,MARK_BALL);
    int num = WM->getPlayerNUmber();
    if(
        (num == 2 || num == 3) &&
        WM->getBallPos().getX() < 0 && WM->getBallPos().getY() < 0;
        ) {
            //盯防函数
            soc = moveToPos(oppPos,PS->getPlayerWhenToTurnAngle());  
    } else if(
        (num == 4 || num == 5) &&
        WM->getBallPos().getX() < 0 && WM->getBallPos().getY() > 0
    ) {
        //盯防函数
        soc = moveToPos(oppPos,PS->getPlayerWhenToTurnAngle()); 
    }
///////////补充代码//////////////////////////////////////////////
}