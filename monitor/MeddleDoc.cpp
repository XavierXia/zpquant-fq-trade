#include "stdafx.h"
#include "MeddleDoc.h"

IMPLEMENT_DYNCREATE(CMeddleDoc, CDocument)
CMeddleDoc::CMeddleDoc()
{
}


CMeddleDoc::~CMeddleDoc()
{
}

void CMeddleDoc::Serialize(CArchive & ar)
{
    if (ar.IsStoring())
    {
        // TODO: �ڴ���Ӵ洢����
    }
    else
    {
        // TODO: �ڴ���Ӽ��ش���
    }
}
