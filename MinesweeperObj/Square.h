#pragma once

//�\���Ֆʂ̏��
typedef int DispState;
const DispState OPENED = 0; //�J���Ă���
const DispState CLOSED = 1; //���Ă���
const DispState MARKED = 2; //�}�[�N����

//�����Ֆʂ̏��
typedef int NonDispState;
const NonDispState NONE = 0; //�����Ȃ�
const NonDispState BOMB = 1; //���e����

//�}�X�Ɋւ���\����
struct Square
{
	int DispState;     //�\���Ֆ�
	int NonDispState;  //�����Ֆ�
	int BombsNum;      //���͂̔��e�̐�
};