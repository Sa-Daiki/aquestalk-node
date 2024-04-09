/************************************************
	AqUsrDic - ���[�U�������C�u����
			AqKanji2Koe/AqKanji2Roman�p

	 COPYRIGHT (C) 2017 AQUEST CORP.

	�y�f�B���N�g���\���z
		<aq_dic>
			|- aqdic.bin	�V�X�e������
			|- aq_usr.dic	���[�U����

	�y���Ӂz
	 ���[�U�����̓V�X�e�������Ɉˑ����邽�߁A
	 �قȂ�V�X�e�������Ƃ̑g�ݍ��킹�͐��퓮�삵�Ȃ��B

	@date	2020/10/09	Ver.4.1

*************************************************/
#pragma once
#ifdef __cplusplus
extern "C"{
#endif

#if (defined _WIN32) || (defined _WIN64)
#define STD_CALL	__stdcall
#else
#define STD_CALL
#endif

//////////////////////////////////////////////////////////////
//	CSV�������烆�[�U����(aq_usr.dic)�𐶐�(�㏑)
//	aq_user.dic�Ɠ����f�B���N�g���ɃV�X�e������(aqdic.bin)�����邱��
//
//	pathUserDic: ���[�U����(aq_user.dic)�t�@�C���̃p�X
//	pathDicCsv:	CSV�����t�@�C���̃p�X
//	return: 0�F����I��	����ȊO�F�G���[
int STD_CALL AqUsrDic_Import(const char *pathUserDic, const char *pathDicCsv);

//////////////////////////////////////////////////////////////
//	���[�U����(aq_usr.dic)����CSV�����𐶐�
//	aq_user.dic�Ɠ����f�B���N�g���ɃV�X�e������(aqdic.bin)�����邱��
//
//	pathUserDic: ���[�U����(aq_user.dic)�t�@�C���̃p�X
//	pathDicCsv:	CSV�����t�@�C���̃p�X
//	return: 0�F����I��	����ȊO�F�G���[
int STD_CALL AqUsrDic_Export(const char *pathUserDic, const char *pathDicCsv);

//////////////////////////////////////////////////////////////
//	�����̃`�F�b�N
//	CSV�����Ɍ��o�����ǉ��E�C������Ƃ��A���[�U�����̐����O��
//	�ǂ݋L����̏����Ȃǂ��`�F�b�N
//
//	surface: ���o���ꕶ����(UTF8)
//	yomi:	��݋L����i�A�N�Z���g�t�������L���� UTF8�j
//	posCode:	�i���R�[�h�i���L�Q�Ɓj
//	return: 0�F�`�F�b�NOK	����ȊO�F�G���[
int STD_CALL AqUsrDic_Check(const char *surface, const char *yomi, int posCode);

//////////////////////////////////////////////////////////////
//	�Ō�̃G���[�̏ڍ׃��b�Z�[�W��Ԃ�
//	�߂�l�F�G���[���b�Z�[�W�iUTF8, NULL�I�[)
const char * STD_CALL AqUsrDic_GetLastError(void);

/*--------------------------
�i���R�[�h(posCode)�F�i����
 0:����
 1:����(�T��)
 2:�l��
 3:�l��(��)
 4:�l��(��)
 5:�ŗL����
 6:�ŗL����(�g�D)
 7:�ŗL����(�n��)
 8:�ŗL����(��)
 9:�㖼��
10:�㖼��(�k��)
11:����(�����\)
12:����(�ڑ����I)
13:����(�`�e�����ꊲ)
14:����(�i�C�`�e���ꊲ)
15:�`�e��
16:����
17:����(�����ސڑ�)
18:�ړ���(�����ڑ�)
19:�ړ���(�����ڑ�)
20:�ړ���(���ڑ�)
21:�ړ���(�`�e���ڑ�)
22:�ڑ���
23:�A�̎�
24:�L��
25:�L��(�A���t�@�x�b�g)
26:������
27:�ԓ���
--------------------------*/

#ifdef __cplusplus
}
#endif
//  ----------------------------------------------------------------------
// !  Copyright AQUEST Corp. 2017- .  All Rights Reserved.                !
// !  An unpublished and CONFIDENTIAL work.  Reproduction, adaptation, or !
// !  translation without prior written permission is prohibited except   !
// !  as allowed under the copyright laws.                                !
//  ----------------------------------------------------------------------
