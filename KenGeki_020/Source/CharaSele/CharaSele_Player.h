﻿//=================================================================================================
//
//	CharaSele Player ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSeleConst.h"
#include "../GameMain/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	class CharaSele_Player : public TASK_VEC
	{
	public:
		//キャラセレ状態
		enum CHST_PL_State
		{
			STT_CHARA,
			STT_COLOR,
			STT_STAGE,
			STT_BGM,
			STT_OK,
		};

	private:
		P_Param			m_pParam;
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラ選択ID
		P_Grp			m_chara_stand;			//キャラ立絵
		bool			m_decided { F };		//決定
		P_Grp			m_chara_stand_light;	//キャラ立絵(明度)
//		P_Grp			m_chara_stand_shade;	//キャラ立絵(影)
		P_Grp			m_chara_name;			//キャラ名前
		P_GrpBlink		m_cursor;				//カーソル
		float			m_x { 0 };				//カットイン位置
		UINT			m_wait { 0 };			//決定ウェイト

		CHST_PL_State	m_state { STT_CHARA };	//状態
		P_GrpBlink		m_state_Disp;			//状態表示

		//定数
		static const uint32		CHARA_SELE_NUM = 12;		//個数
		static const ChSlct		m_pos [ CHARA_SELE_NUM ];	//枠位置

		//CPU
		bool			m_cpu { F };				//CPUかどうか
		bool			m_decide_1P { F };			//1P決定後
		P_Grp			m_grp_Cst_InputPlayerCOM;	//入力者 固定表示"CPU""Player"
		bool			m_Input_1P_Only { F };		//選択操作は１Pのみ
		bool			m_back_to_1p { F };			//2P側から1P側へ戻る

	public:
		CharaSele_Player ();
		CharaSele_Player ( const CharaSele_Player & rhs ) = delete;
		~CharaSele_Player ();

		void ParamInit ( P_Param p );
		void PlayerInit ( PLAYER_ID id );

		void Move ();

		CHARA_SELE_ID GetID () const { return m_chsl_id; }
		CHARA_NAME GetName () const;

		//キャラ名から選択する
		void AssignName ( CHARA_NAME name );

		//状態の取得
		bool IsDecided () const { return m_decided; }
		CHST_PL_State GetState () const { return m_state; }

		bool Is1P() const { return m_player_id == PLAYER_ID_1; }
		bool Is2P() const { return m_player_id == PLAYER_ID_2; }

		//1Pの終了
		bool GetDecide1P () const { return m_decide_1P; }
		void SetDecide1P ( bool b ) { m_decide_1P = b; }

		//2Pから1Pに戻る
		bool GetBackTo1P () const { return m_back_to_1p; }
		void SetBackTo1P ( bool b ) { m_back_to_1p = b; }

		//2Pからキャンセルして1PのBGMに戻る
		void BackTo1pBGM ();


		//外部から見るキー操作
		bool PUSH_KEY_LEFT () const;
		bool PUSH_KEY_RIHGT () const;
		bool PUSH_KEY_DECIDE () const;

	private:
		//状態による分岐
		void Move_Chara ();
		void Move_Color ();
		void Move_Stage ();
		void Move_bgm ();
		void Move_OK ();

		void SetCursorUp ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorDown ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorLeft ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorRight ( P_GrpBlink pCrs, CHARA_SELE_ID & id );

		void Input_Chara ();	//キャラ選択時の入力
		void Input_Color ();	//カラー選択時の入力
		void Input_Stage ();	//ステージ選択時の入力
		void Input_BGM ();		//BGM選択時の入力
		void Input_OK ();		//決定後の入力

		void Cancel ();	//キャンセル
		void Select ();	//カーソル移動で選択時
		void Decide ();	//決定時

		bool CanSelect ();	//選択可能かどうか
		void SetCharaStand ( CHARA_SELE_ID id );
		void HiddenCharaStand ();


		//1Pが両者選択のとき2Pなら操作しない
		bool IsNotSelect () const;

#pragma region CONST

		//カーソル
		//位置定数
		static const float	FACE_X_0;
		static const float	FACE_X_1;
		static const float	FACE_X_2;
		static const float	FACE_Y_0;
		static const float	FACE_Y_1;
		static const float	FACE_Y_2;
		static const float	FACE_Y_3;

		static const float	LOGO_NUM;
		static const float	LOGO_W;
		static const float	LOGO_L_START_Y;
		static const float	LOGO_L_VEL_X;
		static const float	LOGO_R_START_Y;
		static const float	LOGO_R_VEL_X;

#if 0
				//カーソル
		static const float	SELECT_1P_POS_X;	//基準点 + 枠中心 + 画像半分
		static const float	SELECT_1P_POS_Y;
		static const float	SELECT_2P_POS_X;	//基準点 + 枠中心 + 画像半分
		static const float	SELECT_2P_POS_Y;
#endif // 0

		//キャラ立ち絵
		static const float	CHARA_1P_POS_X;
		static const float	CHARA_1P_POS_Y;
		static const float	CHARA_2P_POS_X;
		static const float	CHARA_2P_POS_Y;

		static const float	CUTIN_X;
		static const float	CUTIN_VX;

		//キャラ名前
		static const float	CHARA_NAME_1P_X;
		static const float	CHARA_NAME_1P_Y;
		static const float	CHARA_NAME_2P_X;
		static const float	CHARA_NAME_2P_Y;

		static const float	POS0_X;

		static const float CH_STT_X_1P;
		static const float CH_STT_X_2P;
		static const float CH_STT_CHARA_Y;
		static const float CH_STT_STAGE_Y;
		static const float CH_STT_BGM_Y;
		static const float CH_STT_OK_Y;

		static const uint32		PLAYER;
		static const uint32		CPU;
#pragma endregion
	};


	using P_ChSele_Pl = std::shared_ptr < CharaSele_Player >;


}	//namespace GAME


