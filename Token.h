#define _CRT_SECURE_NO_WARNINGS
#define MAXKEY 1000
/*���ÿ�*/
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include<setjmp.h>
/*��Ҫ����*/
extern jmpret;
extern jmp_buf envbuf;
extern int ident;
extern int fail;
extern int end;
extern jmp_buf envbuf;
extern int JmpRet;
extern int Row;

typedef struct hashTable {
	int token;                    //����
	struct hashTable *next;      //��ϣ����
	char *word;                 //���ַ���
	int count;
}hashNode_t,*phashNode_t;

typedef struct WordList {
	struct WordList *next;                    //������
	struct hashTable *phashNode;              //ָ��ϣ�ڵ�
}WordList_t,*pWordList_t;



void Findhash(phashNode_t *hashNode, phashNode_t node);
void ColorOutput(pWordList_t phead); //��ɫ����ӿ�
void hashInsert(phashNode_t *hashNode, phashNode_t node);
int hash(char *key);      //hash��������������ֵ
void WordTailInsert(pWordList_t *pphead, PWORD *pptail, phashNode_t pInsert);
void alp2word(char *str, int *pos, phashNode_t A);
int count(pWordList_t phead);
void print(pWordList_t *pCur);

void Next(pWordList_t *pCur);
void PR(pWordList_t *pCur);
void UN(pWordList_t *pCur);
void MU(pWordList_t *pCur);
void AD(pWordList_t *pCur);
void RE(pWordList_t *pCur);
void EQ(pWordList_t *pCur);
void A(pWordList_t *pCur);
void E(pWordList_t *pCur);
void print(pWordList_t phead);


enum Token
{
	/* ��������ָ��� */                    
	TK_PLUS=1, // + �Ӻ�1
	TK_MINUS, // - ����2
	TK_STAR, // * �Ǻ�3
	TK_DIVIDE, // / ����4
	TK_MOD, // % ���������5
	TK_EQ, // == ���ں�6
	TK_NEQ, // != �����ں�7
	TK_LT, // < С�ں�8
	TK_LEQ, // <= С�ڵ��ں�9
	TK_GT, // > ���ں�10
	TK_DE, //-=
	TK_GEQ, // >= ���ڵ��ں�11
	TK_ASSIGN, // = ��ֵ�����12
	TK_POINTSTO, // -> ָ��ṹ���Ա�����13
	TK_DOT, // . �ṹ���Ա�����14
	TK_AND, // & ��ַ�������15
	TK_OPENPA, // ( ��Բ����16
	TK_CLOSEPA, // ) ��Բ����17
	TK_OPENBR, // [ ��������18
	TK_CLOSEBR, // ] ��Բ����19
	TK_BEGIN, // { �������20
	TK_END, // } �Ҵ�����21
	TK_SEMICOLON, // ; �ֺ� 22
	TK_COMMA, // , ����23
	TK_ELLIPSIS, // ... ʡ�Ժ�24
	TK_EOF, // �ļ�������25
	TK_AAND, //����26
	TK_OR, //����27
	TK_NO,//����28
	TK_ADD,//����29
	TK_REDUCE,//����30
	TK_jing,  //#
	TK_MAOHAO,// "
	 /* ���� */
	 TK_CINT, // ���ͳ���31
	 TK_CCHAR, // �ַ�����32
	 TK_CSTR, // �ַ�������33
	 TK_FLOAT,// �ַ�������34
	/* �ؼ��� */
	KW_CHAR, // char�ؼ���35
	KW_SHORT, // short�ؼ���36
	KW_INT, // int�ؼ���37
	KW_VOID, // void�ؼ��� 38
	KW_STRUCT, // struct�ؼ��� 39
	KW_IF, // if�ؼ���40
	KW_ELSE, // else�ؼ���41
	KW_FOR, // for�ؼ���42
	KW_CONTINUE, // continue�ؼ���43
	KW_BREAK, // break�ؼ��� 44
	KW_RETURN, // return�ؼ���45
	KW_SIZEOF, // sizeof�ؼ���46
	KW_ALIGN, // __align�ؼ���47
	KW_CDECL, // __cdecl�ؼ��� standard c call48
	KW_STDCALL, // __stdcall�ؼ��� pascal c call49
	KW_main,
	/* ��ʶ�� */
	TK_IDENT, //����50
};



enum Error_type {
	PROGRAM_BEGIN,		//ִ���﷨����
	SUCC,			//�ɹ�
	SOMETHINGWRONG,	//δ֪����
	LACK_SEMICOLON,	//ȱ�ٷֺ�
	RETURN_LACK_SEMICOLON,	//returnȱ�ٷֺ�
	BREAK_LACK_SEMICOLON,	//breakȱ�ٷֺ�
	CONTINUE_LACK_SEMICOLON,	//continueȱ�ٷֺ�
	EXTER_DEC,		//�ⲿ���������ִ���
	LACK_TYPE,		//ȱ������
	ARR_WRONG,		//������������
	LACK_IDENT,		//ȱ�ٱ�ʶ��
	LACK_OPENPA,		//ȱ����Բ����
	LACK_CLOSEPA,		//ȱ����Բ����
	LACK_OPENBR,		//ȱ����������
	LACK_CLOSEBR,		//ȱ����������
	LACK_BEGIN,		//ȱ��������
	LACK_END,			//ȱ���һ�����
	NESTED_FUNC_DECLEAR,//����Ƕ������
	IF_LACK_OPENPA,	//ifȱ����Բ����
	IF_LACK_CLOSEPA,	//ifȱ����Բ����
	FOR_LACK_OPENPA,	//forȱ����Բ����
	FOR_LACK_CLOSEPA,	//forȱ����Բ����
	LACK_PRIMARY		//ȱ�ٳ��ȱ��ʽ
};