#pragma once

//�\���Ֆ�
typedef int DispState;
const DispState OPENED = 0;	//�J���Ă���
const DispState CLOSED = 1;	//���Ă���
const DispState MARKED = 2;	//�}�[�N����

//�����Ֆ�
typedef int NonDispState;
const NonDispState NONE = 0; //�����Ȃ�
const NonDispState BOMB = 1; //���e����

//�C�ӂ̃}�X�Ɋւ���\����
struct Square
{
	int DispState;    //�\���Ֆ�
	int NonDispState; //�����Ֆ�
	int BombsNum;     //���͂̔��e�̐�
};