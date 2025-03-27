//=================================================================================================
//
//	_CharaSele Player ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSeleConst.h"
#include "../GameMain/Param.h"
#include "CharaSele_Image.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele_Player : public TASK_VEC
	{
		P_Param			m_pParam;
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラ選択ID

		P_GrpBlink		m_state_Disp;	//状態表示
		P_ChSl_Img		m_chara_img;	//キャラ立絵

	public:
		_CharaSele_Player ();
		_CharaSele_Player ( const _CharaSele_Player & rhs ) = delete;
		~_CharaSele_Player ();

		void LoadTx ( P_ChSl_Img_Cmn pCmn );
		void ParamInit ( P_Param p );
		void PlayerInit ( PLAYER_ID id );

		void Move ();


	private:

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


	using P_ChSl_Pl = std::shared_ptr < _CharaSele_Player >;


}	//namespace GAME


