//=================================================================================================
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
		P_Param			m_pParam;
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラ選択ID
		P_Grp			m_chara_stand;					//キャラ立絵
		bool			m_decided { F };				//決定
		P_Grp			m_chara_stand_light;			//キャラ立絵(明度)
		P_Grp			m_chara_stand_shade;			//キャラ立絵(影)
		P_Grp			m_chara_name;					//キャラ名前
		P_GrpBlink		m_cursor;						//カーソル
		float			m_x { 0 };		//カットイン位置
		UINT			m_wait { 0 };	//決定ウェイト

		//定数
		static const uint32		CHARA_SELE_NUM = 12;		//個数
		static const ChSlct		m_pos [ CHARA_SELE_NUM ];	//枠位置

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

		bool IsDecided () const { return m_decided; }

	private:
		void SetCursorUp ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorDown ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorLeft ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorRight ( P_GrpBlink pCrs, CHARA_SELE_ID & id );

		void Input ();	//入力
		void Input_Decided ();		//決定後の入力
		void Cancel ();	//キャンセル
		void Select ();	//カーソル移動で選択時
		void Decide ();	//決定時

		bool CanSelect ();	//選択可能かどうか
		void SetCharaStand ( CHARA_SELE_ID id );
		void HiddenCharaStand ();

#pragma region CONST

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

		//カーソル
		static const float	SELECT_1P_POS_X;	//基準点 + 枠中心 + 画像半分
		static const float	SELECT_1P_POS_Y;
		static const float	SELECT_2P_POS_X;	//基準点 + 枠中心 + 画像半分
		static const float	SELECT_2P_POS_Y;

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

#pragma endregion
	};


	using P_ChSele_Pl = std::shared_ptr < CharaSele_Player >;


}	//namespace GAME


