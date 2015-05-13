#include "knowledge.h"

CKnowledge *knowledge;

CKnowledge::CKnowledge(QObject *parent) : QObject(parent)
{
    map = new CMap(27,60, 30,300,3000);
}

CKnowledge::~CKnowledge()
{

}

