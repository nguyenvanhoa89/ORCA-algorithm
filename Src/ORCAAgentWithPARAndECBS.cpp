#include "ORCAAgentWithPARAndECBS.h"



ORCAAgentWithPARAndECBS::ORCAAgentWithPARAndECBS() : Agent()
{
    fakeRadius = 0;
    MAPFAgents = std::set<ORCAAgentWithPARAndECBS *>();
    inMAPFMode = false;
    moveToMAPFPos = false;
    MAPFExec = false;
    MAPFMap = SubMap();

    conf.parallelizePaths1 = true;
    conf.parallelizePaths2 = false;
    conf.maxTime = CN_DEFAULT_MAPF_MAXTIME;
    conf.withFocalSearch = true;
    conf.withCAT = false;
    conf.withPerfectHeuristic = false;
    conf.withCardinalConflicts = false;
    conf.withBypassing = false;
    conf.withMatchingHeuristic = false;
    conf.storeConflicts = true;
    conf.withDisjointSplitting = false;
    conf.focalW = 1;
    conf.planner = "push_and_rotate";
    conf.lowLevel = "astar";

    MAPFVis = false;
    MAPFExec = false;
    MAPFStart = Point(-1,-1);
    MAPFGoal = Point(-1,-1);
    buffMAPF = std::vector<Point>();
    MAPFUnion = false;
    notMAPFVis = false;
    MAPFcommon = Point(-1,-1);
    currMAPFPos = -1;
    MAPFActorId = -1;
    ECBSLLsearch = FocalSearch<>(true, conf.focalW);
    ECBSSolver = ConflictBasedSearch<FocalSearch<>>(&ECBSLLsearch);
    waitForStart = false;
    waitForFinish = false;

    initCount = 0;
    updCount = 0;
    uniCount = 0;
    timeMAPF = 0;
    ECBSCount = 0;
    PARCount = 0;
}



ORCAAgentWithPARAndECBS::ORCAAgentWithPARAndECBS(const int &id, const Point &start, const Point &goal, const Map &map,
                                                 const EnvironmentOptions &options, AgentParam param) : Agent(id, start, goal, map, options, param)
{
    fakeRadius = param.rEps + param.radius;
    MAPFAgents = std::set<ORCAAgentWithPARAndECBS *>();
    inMAPFMode = false;
    moveToMAPFPos = false;
    MAPFVis = false;
    MAPFExec = false;
    MAPFMap = SubMap();

    conf.parallelizePaths1 = true;
    conf.parallelizePaths2 = false;
    conf.maxTime = CN_DEFAULT_MAPF_MAXTIME;
    conf.withFocalSearch = true;
    conf.withCAT = false;
    conf.withPerfectHeuristic = false;
    conf.withCardinalConflicts = false;
    conf.withBypassing = false;
    conf.withMatchingHeuristic = false;
    conf.storeConflicts = true;
    conf.withDisjointSplitting = false;
    conf.focalW = 10.0;
    conf.planner = "push_and_rotate";
    conf.lowLevel = "astar";

    MAPFStart = Point(-1,-1);
    MAPFGoal = Point(-1,-1);
    ECBSLLsearch = FocalSearch<>(true, conf.focalW);
    ECBSSolver = ConflictBasedSearch<FocalSearch<>>(&ECBSLLsearch);
    PARLLsearch = Astar<>(false);
    PARSolver = PushAndRotate(&PARLLsearch);
    buffMAPF = std::vector<Point>();
    MAPFUnion = false;
    notMAPFVis = false;
    MAPFcommon = Point(-1,-1);
    currMAPFPos = -1;
    MAPFActorId = -1;
    waitForStart = false;
    waitForFinish = false;

    initCount = 0;
    updCount = 0;
    uniCount = 0;
    timeMAPF = 0;
    ECBSCount = 0;
    PARCount = 0;
}


ORCAAgentWithPARAndECBS::ORCAAgentWithPARAndECBS(const ORCAAgentWithPARAndECBS &obj) : Agent(obj)
{
    fakeRadius = obj.fakeRadius;
    MAPFAgents = obj.MAPFAgents;
    inMAPFMode = obj.inMAPFMode;
    moveToMAPFPos = obj.moveToMAPFPos;
    MAPFMap = obj.MAPFMap;
    MAPFSet = obj.MAPFSet;
    conf = obj.conf;
    MAPFVis = obj.MAPFVis;
    MAPFExec = obj.MAPFExec;
    MAPFStart = obj.MAPFStart;
    MAPFGoal = obj.MAPFGoal;
    ECBSLLsearch = obj.ECBSLLsearch;
    ECBSSolver = obj.ECBSSolver;
    PARLLsearch = obj.PARLLsearch;
    PARSolver = obj.PARSolver;
    buffMAPF = obj.buffMAPF;
    MAPFUnion = obj.MAPFUnion;
    notMAPFVis = obj.notMAPFVis;
    MAPFcommon = obj.MAPFcommon;
    currMAPFPos = obj.currMAPFPos;
    MAPFActorId = obj.MAPFActorId;
    waitForStart = obj.waitForStart;
    waitForFinish = obj.waitForFinish;
    initCount = obj.initCount;
    updCount = obj.updCount;
    uniCount = obj.uniCount;
    timeMAPF = obj.timeMAPF;
    ECBSCount = obj.ECBSCount;
    PARCount = obj.PARCount;
}


ORCAAgentWithPARAndECBS::~ORCAAgentWithPARAndECBS() = default;


ORCAAgentWithPARAndECBS& ORCAAgentWithPARAndECBS::operator = (const ORCAAgentWithPARAndECBS &obj)
{

    if(this != &obj)
    {
        Agent::operator=(obj);
        fakeRadius = obj.fakeRadius;
        MAPFAgents = obj.MAPFAgents;
        inMAPFMode = obj.inMAPFMode;
        moveToMAPFPos = obj.moveToMAPFPos;
        MAPFMap = obj.MAPFMap;
        MAPFSet = obj.MAPFSet;
        conf = obj.conf;
        MAPFVis = obj.MAPFVis;
        MAPFExec = obj.MAPFExec;
        MAPFStart = obj.MAPFStart;
        MAPFGoal = obj.MAPFGoal;
        ECBSLLsearch = obj.ECBSLLsearch;
        ECBSSolver = obj.ECBSSolver;
        PARLLsearch = obj.PARLLsearch;
        PARSolver = obj.PARSolver;
        buffMAPF = obj.buffMAPF;
        MAPFUnion = obj.MAPFUnion;
        notMAPFVis = obj.notMAPFVis;
        MAPFcommon = obj.MAPFcommon;
        currMAPFPos = obj.currMAPFPos;
        MAPFActorId = obj.MAPFActorId;
        waitForStart = obj.waitForStart;
        waitForFinish = obj.waitForFinish;
        initCount = obj.initCount;
        updCount = obj.updCount;
        uniCount = obj.uniCount;
        timeMAPF = obj.timeMAPF;
        ECBSCount = obj.ECBSCount;
        PARCount = obj.PARCount;
    }
    return *this;
}


void ORCAAgentWithPARAndECBS::ComputeNewVelocity()
{
    if(MAPFExec)
    {
        // Collision count

        unsigned long minMaxNum = (param.agentsMaxNum < Neighbours.size()) ? param.agentsMaxNum : Neighbours.size();

        for(unsigned long i = 0; i < minMaxNum; i++)
        {
            auto curragent = dynamic_cast<ORCAAgentWithPARAndECBS *>(Neighbours[i].second);
            if((curragent->position - position).SquaredEuclideanNorm() <
               (param.radius + curragent->param.radius) * (param.radius + curragent->param.radius))
            {
                collisions++;
            }
        }

        for (int i = 0; i < NeighboursObst.size(); i++)
        {
            Vertex *left = &(NeighboursObst[i].second.left);
            Vertex *right = &(NeighboursObst[i].second.right);

            Vector lRelativePosition = *left - position;
            Vector rRelativePosition = *right - position;

            float lSqDist = lRelativePosition.SquaredEuclideanNorm();
            float rSqDist = rRelativePosition.SquaredEuclideanNorm();

            float sqTrueRadius = param.radius * param.radius;

            Vector obstacleVector = *right - *left;
            float s = -lRelativePosition.ScalarProduct(obstacleVector) / obstacleVector.SquaredEuclideanNorm();
            float lineSqDist = (-lRelativePosition - obstacleVector * s).SquaredEuclideanNorm();

            if ((s < 0.0f && lSqDist < sqTrueRadius) || (s > 1.0f && rSqDist < sqTrueRadius) ||
                (s >= 0.0f && s < 1.0f && lineSqDist < sqTrueRadius))
            {
                collisionsObst++;
            }
        }




        if(currMAPFPos < (*MAPFres.agentsPaths)[MAPFActorId].size())
        {
            auto currGoal =  MAPFMap.GetPoint((*MAPFres.agentsPaths)[MAPFActorId][currMAPFPos]);
            float dist = (currGoal - position).EuclideanNorm();
            newV = (currGoal - position);
            if(dist > 1)
            {
                newV = newV/dist;
            }
            else if(dist < 0.01)
            {
                newV = Point();
            }
        }
        else
        {
            newV = Point();
        }
        Neighbours.clear();
        return;
    }

    ORCALines.clear();

    // Получение ORCA-линий препятсвий
    for (int i = 0; i < NeighboursObst.size(); i++)
    {
        Line line;

        Vertex *left = &(NeighboursObst[i].second.left);
        Vertex *right = &(NeighboursObst[i].second.right);

        Vector lRelativePosition = *left - position;
        Vector rRelativePosition = *right - position;


        bool alreadyCovered = false;

        for (int j = 0; j < ORCALines.size(); j++)
        {
            if ((lRelativePosition * invTimeBoundaryObst - ORCALines[j].liesOn).Det(ORCALines[j].dir) - invTimeBoundaryObst * fakeRadius >= -CN_EPS &&
                (rRelativePosition * invTimeBoundaryObst - ORCALines[j].liesOn).Det(ORCALines[j].dir) - invTimeBoundaryObst * fakeRadius >= -CN_EPS)
            {
                alreadyCovered = true;
                break;
            }
        }
        if (alreadyCovered)
            continue;

        float lSqDist = lRelativePosition.SquaredEuclideanNorm();
        float rSqDist = rRelativePosition.SquaredEuclideanNorm();

        float sqFakeRadius = fakeRadius * fakeRadius;
        float sqTrueRadius = param.radius * param.radius;

        Vector obstacleVector = *right - *left;
        float s = -lRelativePosition.ScalarProduct(obstacleVector) / obstacleVector.SquaredEuclideanNorm();
        float lineSqDist = (-lRelativePosition - obstacleVector * s).SquaredEuclideanNorm();

        if ((s < 0.0f && lSqDist < sqTrueRadius) || (s > 1.0f && rSqDist < sqTrueRadius) ||
            (s >= 0.0f && s < 1.0f && lineSqDist < sqTrueRadius))
        {
            collisionsObst++;
        }


        if (s < 0.0f && lSqDist < sqFakeRadius)
        {

            if (left->IsConvex())
            {
                line.liesOn = Point();
                line.dir = Point(-lRelativePosition.Y(), lRelativePosition.X()) / sqrt(lSqDist); // Построение единичного вектора, нормального к относительному положению
                ORCALines.push_back(line);
            }

            continue;
        }
        else if (s > 1.0f && rSqDist < sqFakeRadius)
        {

            if (right->IsConvex() && rRelativePosition.Det(NeighboursObst[i].second.next->dir) >= 0.0f)
            {
                line.liesOn = Point();
                line.dir = Point(-rRelativePosition.Y(), rRelativePosition.X()) / sqrt(rSqDist);
                ORCALines.push_back(line);
            }

            continue;
        }
        else if (s >= 0.0f && s < 1.0f && lineSqDist < sqFakeRadius)
        {
            line.liesOn = Point();
            line.dir = -(NeighboursObst[i].second.dir);
            ORCALines.push_back(line);
            continue;
        }


        Vector lLegDirection, rLegDirection;

        if (s < 0.0f && lineSqDist <= sqFakeRadius)
        {

            if (!left->IsConvex())
            {
                continue;
            }

            right = left;

            float leg1 = sqrt(lSqDist - sqFakeRadius);

            lLegDirection = Point(lRelativePosition.X() * leg1 - lRelativePosition.Y() * fakeRadius, lRelativePosition.X() * fakeRadius + lRelativePosition.Y() * leg1) / lSqDist;
            rLegDirection = Point(lRelativePosition.X() * leg1 + lRelativePosition.Y() * fakeRadius, -lRelativePosition.X() * fakeRadius + lRelativePosition.Y() * leg1) / lSqDist;
        }
        else if (s > 1.0f && lineSqDist <= sqFakeRadius)
        {

            if (!right->IsConvex())
            {
                continue;
            }

            left = right;

            float leg2 = std::sqrt(rSqDist - sqFakeRadius);
            lLegDirection = Point(rRelativePosition.X() * leg2 - rRelativePosition.Y() * fakeRadius, rRelativePosition.X() * fakeRadius + rRelativePosition.Y() * leg2) / rSqDist;
            rLegDirection = Point(rRelativePosition.X() * leg2 + rRelativePosition.Y() * fakeRadius, -rRelativePosition.X() * fakeRadius + rRelativePosition.Y() * leg2) / rSqDist;
        }
        else
        {
            if (left->IsConvex())
            {
                float leg1 = std::sqrt(lSqDist - sqFakeRadius);
                lLegDirection = Point(lRelativePosition.X() * leg1 - lRelativePosition.Y() * fakeRadius, lRelativePosition.X() * fakeRadius + lRelativePosition.Y() * leg1) / lSqDist;
            }
            else
            {
                lLegDirection = -NeighboursObst[i].second.dir;
            }

            if (right->IsConvex())
            {
                float leg2 = std::sqrt(rSqDist - sqFakeRadius);
                rLegDirection = Point(rRelativePosition.X() * leg2 + rRelativePosition.Y() * fakeRadius, -rRelativePosition.X() * fakeRadius + rRelativePosition.Y() * leg2) / rSqDist;
            }
            else
            {
                rLegDirection = NeighboursObst[i].second.dir;
            }
        }

        ObstacleSegment *leftNeighbor = NeighboursObst[i].second.prev;

        bool isLLegForeign = false, isRLegForeign = false;

        if (left->IsConvex() && lLegDirection.Det(-leftNeighbor->dir) >= 0.0f)
        {
            lLegDirection = -leftNeighbor->dir;
            isLLegForeign = true;
        }

        if (right->IsConvex() && rLegDirection.Det(NeighboursObst[i].second.next->dir) <= 0.0f)
        {
            rLegDirection = NeighboursObst[i].second.next->dir;
            isRLegForeign = true;
        }

        Point leftCutoff = (*left - position) * invTimeBoundaryObst;
        Point rightCutoff = (*right - position) * invTimeBoundaryObst;
        Vector cutoffVec = rightCutoff - leftCutoff;

        const float t = (right == left ? 0.5f : ((currV - leftCutoff).ScalarProduct(cutoffVec)) / cutoffVec.SquaredEuclideanNorm());
        const float tLeft = ((currV - leftCutoff).ScalarProduct(lLegDirection));
        const float tRight = ((currV - rightCutoff).ScalarProduct(rLegDirection));

        if ((t < 0.0f && tLeft < 0.0f) || (left == right && tLeft < 0.0f && tRight < 0.0f))
        {
            Vector unitW = (currV - leftCutoff)/(currV - leftCutoff).EuclideanNorm();

            line.dir = Vector(unitW.Y(), -unitW.X());
            line.liesOn = leftCutoff + unitW * fakeRadius *  invTimeBoundaryObst;
            ORCALines.push_back(line);
            continue;
        }
        else if (t > 1.0f && tRight < 0.0f)
        {
            Vector unitW = (currV - rightCutoff)/(currV - rightCutoff).EuclideanNorm();

            line.dir = Vector(unitW.Y(), -unitW.X());
            line.liesOn = rightCutoff + unitW * fakeRadius * invTimeBoundaryObst ;
            ORCALines.push_back(line);
            continue;
        }

        float cutoffSqDist = ((t < 0.0f || t > 1.0f || right == left) ? std::numeric_limits<float>::infinity() : (currV - (leftCutoff + cutoffVec * t)).SquaredEuclideanNorm());
        float lLegSqDist = ((tLeft < 0.0f) ? std::numeric_limits<float>::infinity() : (currV - (leftCutoff + lLegDirection * tLeft)).SquaredEuclideanNorm());
        float rLegSqDist = ((tRight < 0.0f) ? std::numeric_limits<float>::infinity() : (currV - (rightCutoff + rLegDirection * tRight)).SquaredEuclideanNorm());

        if (cutoffSqDist <= lLegSqDist && cutoffSqDist <= rLegSqDist)
        {
            line.dir = -NeighboursObst[i].second.dir;
            line.liesOn = leftCutoff + Point(-line.dir.Y(), line.dir.X()) * fakeRadius * invTimeBoundaryObst;
            ORCALines.push_back(line);
            continue;
        }
        else if (lLegSqDist <= rLegSqDist)
        {
            if (isLLegForeign)
            {
                continue;
            }

            line.dir = lLegDirection;
            line.liesOn = leftCutoff + Point(-line.dir.Y(), line.dir.X()) * fakeRadius * invTimeBoundaryObst;;
            ORCALines.push_back(line);
            continue;
        }
        else
        {
            if (isRLegForeign)
            {
                continue;
            }

            line.dir = -rLegDirection;
            line.liesOn = rightCutoff + Point(-line.dir.Y(), line.dir.X()) * fakeRadius * invTimeBoundaryObst;
            ORCALines.push_back(line);
            continue;
        }
    }


    size_t numObstLines = ORCALines.size();

    //Получение ORCA-линий агентов
    //std::sort(Neighbours.begin(),Neighbours.end(), Compare);

    Line currline;
    ORCAAgentWithPARAndECBS *curragent;
    Vector u, w;

    unsigned long minMaxNum = (param.agentsMaxNum < Neighbours.size()) ? param.agentsMaxNum : Neighbours.size();

    for(unsigned long i = 0; i < minMaxNum; i++)
    {
        auto Neighbour = Neighbours[i];
        curragent = dynamic_cast<ORCAAgentWithPARAndECBS *>(Neighbour.second);
        auto circlecenter = curragent->position - this->position; //(P_b - P_a)
        auto relvelocity = this->currV - curragent->currV; //(V_a - V_b)

        float radiussum = fakeRadius + curragent->fakeRadius; //(R_a + R_b)
        float radiussum2 = radiussum * radiussum;
        float distSq = circlecenter.SquaredEuclideanNorm();
        float trueSqRadSum = (param.radius + curragent->param.radius) * (param.radius + curragent->param.radius);

        if(distSq < trueSqRadSum )
        {
            collisions++;
        }

        if(distSq >= radiussum2)
        {
            w = relvelocity - (circlecenter * invTimeBoundary); //w -- вектор на плоскости скоростей от центра малой окружности (основания VO) до скорости другого агента относительно этого
            float sqwlength = w.SquaredEuclideanNorm();
            float wproj = w.ScalarProduct(circlecenter);

            // если эти условия выполняются, то вектор w отложенный из центра окружности-основания VO будет своим концом ближе к
            // этой самой окружности, а значит и ближайшая точка на границе VO -- это какая-то точка на этой окружнрости

            if(wproj < 0.0f && (wproj * wproj) > sqwlength * radiussum2)
            {
                const float wlength = std::sqrt(sqwlength);
                const Vector nw = w / wlength;
                currline.dir = Vector(nw.Y(), -nw.X());
                u = nw * (radiussum * invTimeBoundary - wlength);
            }
            else
            {
                //иначе проекция на стороны VO
                //длина проекции вектора относительных положений на сторону VO

                float leg = std::sqrt(distSq - radiussum2);

                if(circlecenter.Det(w) > 0.0f) //если точка ближе к левой стороне VO
                {
                    currline.dir = Vector(circlecenter.X() * leg - circlecenter.Y() * radiussum, circlecenter.X() * radiussum + circlecenter.Y() * leg) / distSq;
                }
                else //если точка ближе к правой стороне VO
                {
                    currline.dir = -(Vector(circlecenter.X() * leg + circlecenter.Y() * radiussum, -circlecenter.X() * radiussum + circlecenter.Y() * leg) / distSq);
                }

                float rvproj = relvelocity.ScalarProduct(currline.dir);

                u = currline.dir * rvproj - relvelocity;
            }
        }
        else
        {
            const float invTimeStep = 1.0f / options->timestep;

            Vector w = relvelocity - circlecenter * invTimeStep;
            float wlength = w.EuclideanNorm();
            Vector wn = w / wlength;
            currline.dir = Vector(wn.Y(), -wn.X());
            u = wn * (radiussum * invTimeStep - wlength);
        }

        currline.liesOn = this->currV + u * 0.5f;
        ORCALines.push_back(currline);
        Neighbours.pop_back();
    }

    auto lineFail = Utils::linearProgram2(ORCALines, param.maxSpeed, this->prefV, false, this->newV);
    if(lineFail < this->ORCALines.size())
    {
        Utils::linearProgram3(ORCALines, numObstLines, lineFail, param.maxSpeed, this->newV);
    }

    Neighbours.clear();
}


void ORCAAgentWithPARAndECBS::ApplyNewVelocity()
{
    MAPFVis = false;
    notMAPFVis = false;
    MAPFUnion = false;
    currV = newV;
    waitForStart = false;
    waitForFinish = false;

    speedSaveBuffer.pop_front();
    if(inMAPFMode)
    {
        speedSaveBuffer.push_back(1.0f);
    }
    else
    {
        speedSaveBuffer.push_back(currV.EuclideanNorm());
    }


    float mean = 0.0f;

    for(auto speed : speedSaveBuffer)
    {
        mean += speed;
    }

    mean /= speedSaveBuffer.size();
    meanSavedSpeed = mean;
}


bool ORCAAgentWithPARAndECBS::UpdatePrefVelocity()
{
    Point next;
    if(inMAPFMode)
    {
        //std::cout<<id << " " << PARActorId << " " << PARExec << " " << PARAgents.size() << " X: " << PARStart.X() << " Y: " << PARStart.Y() << " Xpos: " << position.X() << " Ypos: " << position.Y() << "\n";

        if(MAPFUnion)
        {
            UniteMAPF();
            prefV = Point();
            nextForLog = position;
            return true;
        }

        if(notMAPFVis)
        {
            UpdateMAPF();
            prefV = Point();
            nextForLog = position;
            return true;
        }

        if(MAPFExec)
        {
            nextForLog = MAPFGoal;
            bool allOnPos = true;
            bool allFin = true;

            for(auto& ag : MAPFAgents)
            {
                int agMAPFId = ag->MAPFActorId;
                if(agMAPFId == -1 && !ag->inMAPFMode)
                {
                    continue;
                }

                int agMAPFPos = (currMAPFPos < (*(MAPFres.agentsPaths))[agMAPFId].size()) ? currMAPFPos : int((*(MAPFres.agentsPaths))[agMAPFId].size() - 1);
                Point agCurrGoal =  MAPFMap.GetPoint((*(MAPFres.agentsPaths))[agMAPFId][agMAPFPos]);

                if(!((ag->position - agCurrGoal).EuclideanNorm() < options->delta) || !ag->MAPFExec)
                {
                    allOnPos = false;
                }

                if(!((ag->position - ag->MAPFGoal).EuclideanNorm() < options->delta) && ag->inMAPFMode)
                {
                    allFin = false;
                }
            }

            if(allFin)
            {
//                std::cout<<"Fin\n";
                waitForFinish = true;
                inMAPFMode = false;
                MAPFExec = false;
                moveToMAPFPos = false;
                currMAPFPos = -1;
                MAPFActorId = -1;
                MAPFStart = Point(-1,-1);
                MAPFGoal = Point(-1,-1);
                prefV = Point();
                nextForLog = position;
                MAPFres.Clear();
                MAPFAgents.clear();
                MAPFcommon = Point();
                MAPFSet.clear();
                buffMAPF.clear();
                return true;
            }
            else if(allOnPos)
            {
                currMAPFPos++;
            }
            else
            {
                prefV = Point();
                nextForLog = MAPFGoal;
                return true;
            }



        }

        if(moveToMAPFPos)
        {
            if(waitForStart)
            {
                waitForStart = false;
                MAPFExec = false;
                nextForLog = MAPFStart;
                prefV = Point();
                return true;
            }
            nextForLog = MAPFStart;
            float dist = (position-MAPFStart).EuclideanNorm();
            if(dist < options->delta)
            {

                prefV = Point();
                MAPFExec = true;

                for(auto &a : MAPFAgents)
                {
                    float distOtherAgent = (a->position - a->MAPFStart).EuclideanNorm();
                    if(!(distOtherAgent < options->delta))
                    {
                        MAPFExec = false;
                        break;
                    }
                }

                if(MAPFExec)
                {
                    nextForLog = MAPFGoal;
                    moveToMAPFPos = false;
                    currMAPFPos = 1;

                    return true;
                }
                else
                {
                    MAPFExec = false;
                    return true;
                }
            }
            else
            {
                nextForLog = MAPFStart;
                Vector goalVector = MAPFStart - position;
                float dist = goalVector.EuclideanNorm();

                if(dist > 1)
                {
                    goalVector = (goalVector/dist);
                }
                prefV = goalVector;
                return true;
            }
        }
    }
    else
    {
        if(MAPFVis)
        {
            prefV = Point();
            return true;
        }
        if(planner->GetNext(position, next))
        {
            nextForLog = next;
            Vector goalVector = next - position;
            float dist = goalVector.EuclideanNorm();
            if((options->trigger == MAPFTriggers::COMMON_POINT && CommonPointMAPFTrigger(dist)) ||
               (options->trigger == MAPFTriggers::SPEED_BUFFER && MeanSavedSpeedMAPFTrigger()))
            {
                PrepareMAPFExecution(next);
                prefV = Point();

                return true;
            }
            else
            {
                if(next == goal && dist < options->delta)
                {
                    prefV = Point();
                    return true;
                }

                if(dist > CN_EPS)
                {
                    goalVector = (goalVector/dist) * param.maxSpeed;
                }

                prefV = goalVector;
                return true;
            }
        }
        nextForLog = position;
        prefV = Point();
        return false;
    }

}


bool ORCAAgentWithPARAndECBS::operator == (const ORCAAgentWithPARAndECBS &another) const
{
    return this->id == another.id;
}


bool ORCAAgentWithPARAndECBS::operator != (const ORCAAgentWithPARAndECBS &another) const
{
    return this->id != another.id;
}


ORCAAgentWithPARAndECBS* ORCAAgentWithPARAndECBS::Clone() const
{
    return new ORCAAgentWithPARAndECBS(*this);
}


void ORCAAgentWithPARAndECBS::AddNeighbour(Agent &neighbour, float distSq)
{
    float sightSq = param.sightRadius * param.sightRadius;

    if(!(distSq < sightSq))
    {
        return;
    }

    int i = 0;
    auto tmpit = Neighbours.begin();
    while(tmpit != Neighbours.end() && i < param.agentsMaxNum && Neighbours[i].first < distSq)
    {
        i++;
        tmpit++;
    }
    if(i < param.agentsMaxNum)
    {
        Neighbours.insert(tmpit,std::pair<float, Agent *>(distSq, &neighbour));

        auto tmpAgentMAPF = dynamic_cast<ORCAAgentWithPARAndECBS*>(&neighbour);
        if(tmpAgentMAPF->inMAPFMode)
        {
            MAPFVis = true;

            if(inMAPFMode)
            {
                if( !tmpAgentMAPF->MAPFUnion && MAPFAgents.find(tmpAgentMAPF) == MAPFAgents.end())
                {
                    if(distSq < (param.radius + tmpAgentMAPF->param.radius + 0.25) * (param.radius + tmpAgentMAPF->param.radius + 0.25))
                    {
                        MAPFUnion = true;
                    }
                }
            }
        }
        else if(inMAPFMode)
        {
            notMAPFVis = true;
        }
    }
}


std::set<ORCAAgentWithPARAndECBS *> ORCAAgentWithPARAndECBS::GetAgentsForCentralizedPlanning()
{
    return MAPFAgents;
}


void ORCAAgentWithPARAndECBS::SetAgentsForCentralizedPlanning(std::set<ORCAAgentWithPARAndECBS *> agents)
{
    MAPFAgents = agents;
}


std::vector<std::pair<float, Agent *>>& ORCAAgentWithPARAndECBS::GetNeighbours()
{
    return Neighbours;
}


bool ORCAAgentWithPARAndECBS::ComputeMAPFEnv(Point common, std::vector<std::pair<Point, ORCAAgentWithPARAndECBS*>> oldGoals)
{

    float minX = map->GetWidth() * map->GetCellSize(), minY = map->GetHeight() * map->GetCellSize(), maxX = 0, maxY = 0;

    for(auto &ag : MAPFAgents)
    {
        if((ag->GetPosition().X() - ag->param.sightRadius) < minX)
        {
            minX = (ag->GetPosition().X() - ag->param.sightRadius);
        }
        if((ag->GetPosition().Y() - ag->param.sightRadius) < minY)
        {
            minY = (ag->GetPosition().Y() - ag->param.sightRadius);
        }

        if((ag->GetPosition().X() + ag->param.sightRadius) > maxX)
        {
            maxX = (ag->GetPosition().X() + ag->param.sightRadius);
        }
        if((ag->GetPosition().Y() + ag->param.sightRadius) > maxY)
        {
            maxY = (ag->GetPosition().Y() + ag->param.sightRadius);
        }
    }

    Node nodeLeftTop = map->GetClosestNode(Point(minX, maxY));
    Node nodeRightBottom = map->GetClosestNode(Point(maxX, minY));
    int width = nodeRightBottom.j - nodeLeftTop.j + 1;
    int height = nodeRightBottom.i - nodeLeftTop.i + 1;
    MAPFMap = SubMap(map, nodeLeftTop, {height,width}, 1);

    // Starts and goals
    std::unordered_map<int, Node> starts;
    std::unordered_map<int, Node> goals;
    for(auto &og : oldGoals)
    {
        Node tmpOldGoal = MAPFMap.GetClosestNode(og.first);
        if(goals.find(tmpOldGoal.i * MAPFMap.GetWidth() + tmpOldGoal.j) == goals.end())
        {
            goals.insert({tmpOldGoal.i * MAPFMap.GetWidth() + tmpOldGoal.j, tmpOldGoal});
        }
        else
        {
            og.second->MAPFGoal = Point(-1,-1);
            while(!og.second->buffMAPF.empty())
            {
                og.second->planner->AddPointToPath(og.second->buffMAPF.back());
                og.second->buffMAPF.pop_back();
            }
        }

    }

    MAPFSet = MAPFActorSet();
    MAPFSet.clear();
    Point tmpGoalPoint;
    for(auto &ag : MAPFAgents)
    {
        Node tmpStart, tmpGoal;

        if(ag->MAPFGoal.X() < 0)
        {
            ag->buffMAPF.clear();
            tmpGoalPoint = ag->PullOutIntermediateGoal(common);
            tmpGoal = MAPFMap.GetClosestNode(tmpGoalPoint);
            tmpGoal = MAPFMap.FindAvailableNode(tmpGoal, goals);


            if(tmpGoal.i < 0)
            {
                for(auto &ag1 : MAPFAgents)
                {
                    while(!ag1->buffMAPF.empty())
                    {
                        ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                        ag1->buffMAPF.pop_back();
                    }
                    ag1->MAPFStart = Point(-1,-1);
                    ag1->MAPFGoal = Point(-1,-1);
                    ag1->inMAPFMode = false;
                    ag1->moveToMAPFPos = false;
                    ag1->MAPFVis = false;
                    ag1->MAPFExec = false;
                }

                return false;
            }

            ag->MAPFGoal = MAPFMap.GetPoint(tmpGoal);

        }
        else
        {
            tmpGoal = MAPFMap.GetClosestNode(ag->MAPFGoal);
            ag->MAPFGoal = MAPFMap.GetPoint(tmpGoal);
            // std::cout << ag->id << " goal1: " << ag->MAPFGoal.ToString() << " goal2: " << MAPFMap.GetPoint(tmpGoal).ToString() << "\n";
        }


        if(ag->MAPFStart.X() < 0)
        {
            tmpStart = MAPFMap.GetClosestNode(ag->GetPosition());
            tmpStart = MAPFMap.FindAvailableNode(tmpStart, starts);

            if(tmpStart.i < 0)
            {
                for(auto &ag1 : MAPFAgents)
                {
                    while(!ag1->buffMAPF.empty())
                    {
                        ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                        ag1->buffMAPF.pop_back();
                    }
                    ag1->MAPFStart = Point(-1,-1);
                    ag1->MAPFGoal = Point(-1,-1);
                    ag1->inMAPFMode = false;
                    ag1->moveToMAPFPos = false;
                    ag1->MAPFVis = false;
                    ag1->MAPFExec = false;
                }
                return false;
            }
            ag->MAPFStart = MAPFMap.GetPoint(tmpStart);
        }
        else
        {
            tmpStart = MAPFMap.GetClosestNode(ag->MAPFStart);
        }

        starts.insert({tmpStart.i * MAPFMap.GetWidth() + tmpStart.j, tmpStart});

        goals.insert({tmpGoal.i * MAPFMap.GetWidth() + tmpGoal.j, tmpGoal});

        MAPFSet.addActor(tmpStart.i, tmpStart.j, tmpGoal.i, tmpGoal.j);
        if(ag == this)
        {
            MAPFActorId = MAPFSet.getActorId(tmpStart.i, tmpStart.j);
            currMAPFPos = 0;
        }
    }
    return true;
}


Point ORCAAgentWithPARAndECBS::PullOutIntermediateGoal(Point common)
{
    Point nextPoint = planner->PullOutNext();
    buffMAPF.push_back(nextPoint);
    if(nextPoint == common)
    {
        Point nextNextPoint = planner->PullOutNext();
        buffMAPF.push_back(nextNextPoint);
        return nextNextPoint;
    }

    return nextPoint;
}


int ORCAAgentWithPARAndECBS::ComputeMAPF(int algToUse)
{
//    PARSolver.clear();
    conf.maxTime = CN_DEFAULT_MAPF_MAXTIME;
    PARLLsearch = Astar<>(false);
    PARSolver = PushAndRotate(&PARLLsearch);

    auto PARSet = MAPFSet;
    fallbackMAPFRes = PARSolver.startSearch(MAPFMap, conf, PARSet);

    if(fallbackMAPFRes.pathfound && algToUse != ONLY_PAR)
    {
        ECBSLLsearch = FocalSearch<>(true, conf.focalW);
        ECBSSolver = ConflictBasedSearch<FocalSearch<>>(&ECBSLLsearch);
        conf.maxTime = CN_DEFAULT_MAPF_MAXTIME - static_cast<int>(ceil(fallbackMAPFRes.time));

        auto ECBSRes = ECBSSolver.startSearch(MAPFMap, conf, MAPFSet);
        if (ECBSRes.pathfound)
        {
            MAPFres = ECBSRes;
            return PAR_AND_ECBS;
        }
    }

    MAPFres = fallbackMAPFRes;
    conf.maxTime = CN_DEFAULT_MAPF_MAXTIME;
    return (MAPFres.pathfound) ? ONLY_PAR : FAIL;
}


void ORCAAgentWithPARAndECBS::PrepareMAPFExecution(Point common)
{
    MAPFAgents.clear();
    inMAPFMode = true;
    moveToMAPFPos = true;
    MAPFExec = false;

    MAPFAgents.insert(this);
    for (auto &el : Neighbours)
    {
        ORCAAgentWithPARAndECBS * neighbour = dynamic_cast<ORCAAgentWithPARAndECBS *>(el.second);
        if(!neighbour->inMAPFMode && !neighbour->waitForFinish)
        {
            MAPFAgents.insert(neighbour);
            neighbour->inMAPFMode = true;
            neighbour->moveToMAPFPos = true;
            neighbour->MAPFExec = false;
            neighbour->prefV = Point();

            for(auto &el2 : neighbour->GetNeighbours())
            {
                auto neighbourOfNeighbour = dynamic_cast<ORCAAgentWithPARAndECBS *>(el2.second);
                if(!neighbourOfNeighbour->inMAPFMode && !neighbourOfNeighbour->waitForFinish)
                {
                    neighbourOfNeighbour->inMAPFMode = true;
                    neighbourOfNeighbour->moveToMAPFPos = true;
                    neighbourOfNeighbour->MAPFExec = false;
                    neighbourOfNeighbour->prefV = Point();
                    MAPFAgents.insert(neighbourOfNeighbour);
                }
            }
        }
    }

    for(auto &ag : MAPFAgents)
    {
        if(ag != this)
        {
            ag->SetAgentsForCentralizedPlanning(MAPFAgents);
        }
        if (!ag->ComputeMAPFEnv(common))
        {
            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFExec = false;
                ag1->currMAPFPos = -1;
                ag1->MAPFActorId = -1;
            }
            return;
        }
    }



    int algToUse = PAR_AND_ECBS;
    int algUsed;
    auto startpnt = std::chrono::high_resolution_clock::now();
    for(auto &ag : MAPFAgents)
    {
        algUsed = ag->ComputeMAPF(algToUse);
        if(!algUsed)
        {

            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFExec = false;
                ag1->currMAPFPos = -1;
                ag1->MAPFActorId = -1;
            }
            return;
        }

        if((algToUse = algUsed) == ONLY_PAR)
        {
            for(auto ag1 = MAPFAgents.begin(); *ag1 != ag; ag1++)
            {
                (*ag1)->MAPFres = (*ag1)->fallbackMAPFRes;
            }
        }

    }

    auto endpnt = std::chrono::high_resolution_clock::now();
    size_t res = std::chrono::duration_cast<std::chrono::milliseconds>(endpnt - startpnt).count();

    if(algUsed == ONLY_PAR)
    {
        PARCount++;
    }
    else
    {
        ECBSCount++;
    }

#if MAPF_LOG
    // Save here
    MAPFLog->SaveInstance(MAPFSet, MAPFMap, conf);
#endif

    for(auto &ag : MAPFAgents)
    {
        ag->inMAPFMode = true;
        ag->moveToMAPFPos = true;
        ag->MAPFVis = false;
        ag->MAPFExec = false;
        ag->MAPFcommon = common;
        ag->currMAPFPos = 0;
        ag->waitForStart = true;
        //std::cout << ag->id << " " << ag->PARActorId << " " << ag->currPARPos << "\n";
    }
    initCount++;
    timeMAPF += (static_cast<float>(res) / MAPFAgents.size());
}


bool ORCAAgentWithPARAndECBS::UniteMAPF()
{

    MAPFUnion = false;
    for(auto &ag : MAPFAgents)
    {
        ag->MAPFStart = Point(-1,-1);
        ag->MAPFGoal = Point(-1,-1);
        ag->MAPFres.Clear();
        ag->currMAPFPos = -1;
        ag->MAPFActorId = -1;
        ag->MAPFUnion = false;
    }


    for(auto &el : Neighbours)
    {
        ORCAAgentWithPARAndECBS * neighbour = dynamic_cast<ORCAAgentWithPARAndECBS *>(el.second);
        if(neighbour->inMAPFMode && !neighbour->waitForFinish && MAPFAgents.find(neighbour) == MAPFAgents.end())
        {
            for(auto& nn : neighbour->MAPFAgents)
            {
                while(!nn->buffMAPF.empty())
                {
                    nn->planner->AddPointToPath(nn->buffMAPF.back());
                    nn->buffMAPF.pop_back();
                }

                nn->MAPFStart = Point(-1,-1);
                nn->MAPFGoal = Point(-1,-1);
                nn->currMAPFPos = -1;
                nn->MAPFActorId = -1;
                nn->MAPFUnion = false;
                nn->MAPFres.Clear();
            }

            MAPFAgents.insert(neighbour->MAPFAgents.begin(), neighbour->MAPFAgents.end());
        }
    }


    for(auto &ag : MAPFAgents)
    {
        if(ag != this)
        {
            ag->SetAgentsForCentralizedPlanning(MAPFAgents);
        }
        if (!ag->ComputeMAPFEnv(MAPFcommon))
        {
            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFExec = false;
                ag1->currMAPFPos = -1;
                ag1->MAPFActorId = -1;
            }
            return false;
        }
    }

    int algToUse = PAR_AND_ECBS;
    int algUsed;
    auto startpnt = std::chrono::high_resolution_clock::now();
    for(auto &ag : MAPFAgents)
    {
        algUsed = ag->ComputeMAPF(algToUse);

        if(!algUsed)
        {
#if PAR_LOG
            MAPFLog->AddResults(ag->MAPFres);
#endif
            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFExec = false;
                ag1->currMAPFPos = -1;
                ag1->MAPFActorId = -1;
            }
            return false;
        }

        if((algToUse = algUsed) == ONLY_PAR)
        {
            for(auto ag1 = MAPFAgents.begin(); *ag1 != ag; ag1++)
            {
                (*ag1)->MAPFres = (*ag1)->fallbackMAPFRes;
            }
        }

    }
    auto endpnt = std::chrono::high_resolution_clock::now();
    size_t res = std::chrono::duration_cast<std::chrono::milliseconds>(endpnt - startpnt).count();
    if(algUsed == ONLY_PAR)
    {
        PARCount++;
    }
    else
    {
        ECBSCount++;
    }

    for(auto &ag : MAPFAgents)
    {
        ag->inMAPFMode = true;
        ag->moveToMAPFPos = true;
        ag->MAPFVis = false;
        ag->MAPFExec = false;
        ag->MAPFcommon = MAPFcommon;
        ag->currMAPFPos = 0;
        ag->waitForStart = true;
    }
    uniCount++;
    timeMAPF += (static_cast<float>(res) / MAPFAgents.size());
    return true;

}


bool ORCAAgentWithPARAndECBS::UpdateMAPF()
{

    for(auto &ag : MAPFAgents)
    {
        ag->MAPFStart = Point(-1,-1);
        ag->MAPFGoal = Point(-1,-1);
        ag->MAPFres.Clear();
        ag->currMAPFPos = -1;
        ag->MAPFActorId = -1;

    }

    std::set<ORCAAgentWithPARAndECBS*> tmpAgents;
    for(auto &ag : MAPFAgents)
    {

        auto N = ag->GetNeighbours();
        for(auto &el : N)
        {
            ORCAAgentWithPARAndECBS *neighbour = dynamic_cast<ORCAAgentWithPARAndECBS *>(el.second);
            if(!neighbour->inMAPFMode && !neighbour->waitForFinish)
            {
                neighbour->MAPFStart = Point(-1,-1);
                neighbour->MAPFGoal = Point(-1,-1);
                neighbour->MAPFres.Clear();
                neighbour->currMAPFPos = -1;
                neighbour->MAPFActorId = -1;
                tmpAgents.insert(neighbour);
            }
        }
        ag->notMAPFVis = false;
    }

    MAPFAgents.insert(tmpAgents.begin(), tmpAgents.end());

    for(auto &ag : MAPFAgents)
    {
        if(ag != this)
        {
            ag->SetAgentsForCentralizedPlanning(MAPFAgents);
        }

        if (!ag->ComputeMAPFEnv(MAPFcommon))
        {
            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFExec = false;
                ag1->currMAPFPos = -1;
                ag1->MAPFActorId = -1;
            }
            return false;
        }
    }

    int algToUse = PAR_AND_ECBS;
    int algUsed;
    auto startpnt = std::chrono::high_resolution_clock::now();
    for(auto &ag : MAPFAgents)
    {
        algUsed = ag->ComputeMAPF(algToUse);
        //std::cout<< algUsed << std::endl;
        if(!algUsed)
        {
#if PAR_LOG
            MAPFLog->AddResults(ag->MAPFres);
#endif
            for(auto &ag1 : MAPFAgents)
            {
                while(!ag1->buffMAPF.empty())
                {
                    ag1->planner->AddPointToPath(ag1->buffMAPF.back());
                    ag1->buffMAPF.pop_back();
                }

                ag1->MAPFStart = Point(-1,-1);
                ag1->MAPFGoal = Point(-1,-1);
                ag1->inMAPFMode = false;
                ag1->moveToMAPFPos = false;
                ag1->MAPFVis = false;
                ag1->MAPFExec = false;
            }
            return false;
        }

        if((algToUse = algUsed) == ONLY_PAR)
        {
            for(auto ag1 = MAPFAgents.begin(); *ag1 != ag; ag1++)
            {
                (*ag1)->MAPFres = (*ag1)->fallbackMAPFRes;
            }
        }

    }
    auto endpnt = std::chrono::high_resolution_clock::now();
    size_t res = std::chrono::duration_cast<std::chrono::milliseconds>(endpnt - startpnt).count();
    if(algUsed == ONLY_PAR)
    {
        PARCount++;
    }
    else
    {
        ECBSCount++;
    }

    for(auto &ag : MAPFAgents)
    {
        ag->inMAPFMode = true;
        ag->moveToMAPFPos = true;
        ag->MAPFVis = false;
        ag->MAPFExec = false;
        ag->MAPFcommon = MAPFcommon;
        ag->currMAPFPos = 0;
        ag->waitForStart = true;
        //std::cout << ag->id << " " << ag->PARActorId << " " << ag->currPARPos << "\n";
    }
    updCount++;
    timeMAPF += (static_cast<float>(res) / MAPFAgents.size());
    return true;
}


bool ORCAAgentWithPARAndECBS::isMAPFMember() const
{
    return inMAPFMode;
}

#if PAR_LOG
void ORCAAgenWithMAPFAndECBS::SetMAPFInstanceLoggerRef(MAPFInstancesLogger *log)
{
    MAPFLog = log;
}
#endif

unordered_map<std::string, float> ORCAAgentWithPARAndECBS::GetMAPFStatistics() const
{
    size_t allMapfCount = initCount + uniCount + updCount;

    unordered_map<std::string, float> stat;
    stat[CNS_MAPF_COMMON_TIME] = timeMAPF;
    stat[CNS_MAPF_INIT_COUNT] = static_cast<float>(initCount);
    stat[CNS_MAPF_UNITE_COUNT] = static_cast<float>(uniCount);
    stat[CNS_MAPF_UPDATE_COUNT] = static_cast<float>(updCount);
    stat[CNS_MAPF_ECBS_COUNT] = static_cast<float>(ECBSCount);
    stat[CNS_MAPF_PAR_COUNT] = static_cast<float>(PARCount);

    return stat;
}