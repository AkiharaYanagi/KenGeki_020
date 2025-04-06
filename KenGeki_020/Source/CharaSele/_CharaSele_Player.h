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
#include "_CharaSele_Actor.h"
#include "CharaSele_Cursor.h"
#include "CharaSele_Image.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele_Player : public TASK_VEC, public std::enable_shared_from_this < _CharaSele_Player >
	{
		P_Param			m_pParam;
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別

		//@info shared_from_thisは実体ではなくポインタで保持したオブジェクトでしか取れない
		P_ChSl_Actor	m_actor;	//状態アクタ

		P_GrpBlink		m_state_Disp;	//状態表示


//		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラ選択ID

		CHARA_COLOR		m_color { CH_CLR_1 };			//カラー
		P_GrpBlink		m_txt_ClrSl;	//カラーセレクト文字表示
		P_GrpBlink		m_Arw_ClrSl;	//カラーセレクト矢印表示
		P_Grp			m_Num_ClrSl;	//カラーセレクト番号表示

		P_ChSl_Cursor	m_cursor;		//カーソル
		P_ChSl_Img		m_chara_img;	//キャラ立絵

	public:
		_CharaSele_Player ();
		_CharaSele_Player ( const _CharaSele_Player & rhs ) = delete;
		~_CharaSele_Player ();

		void LoadTx ( P_ChSl_Img_Cmn pCmn );
		void PlayerInit ( PLAYER_ID id );
		void ParamInit ( P_Param p );

		void Load ();
		void Move ();
		void Input ();

		//参照
		void SetwpCharaSele ( WP_CharaSele wp ) { m_actor->SetwpCharaSele ( wp ); }

		//プレイヤ取得
		PLAYER_ID GetPlayerID () const { return m_player_id; }


		//キャラ選択
		void SelectChara_cutin ( CHARA_SELE_ID chara_id );
		void SelectChara ( CHARA_SELE_ID chara_id );
		CHARA_NAME GetCharaName () const;

		//カラー選択
		CHARA_COLOR GetColor () const { return m_color; }
		void SelectColor_cutin ( CHARA_COLOR chara_clr );
		void SelectColor ( CHARA_COLOR chara_clr );

		//状態を変更
		void To_Chara ();
		void To_Color ();
		void To_Stage ();
		void To_BGM ();
		void To_OK ();

		bool Is_OK () const { return m_actor->Is_OK(); }

	private:

		//パラメータ キャラ名から選択する
		void AssignName ( CHARA_NAME name );

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

		//選択状態カーソル位置
		static const float CH_STT_X_1P;
		static const float CH_STT_X_2P;
		static const float CH_STT_CHARA_Y;
		static const float CH_STT_COLOR_1P_X;
		static const float CH_STT_COLOR_2P_X;
		static const float CH_STT_COLOR_Y;
		static const float CH_STT_STAGE_Y;
		static const float CH_STT_BGM_Y;
		static const float CH_STT_OK_Y;

		//カラーセレクト文字表示
		static const float TXT_CLR_SL_1P_X;
		static const float TXT_CLR_SL_2P_X;
		static const float TXT_CLR_SL_Y;

		//カラーセレクト矢印表示
		static const float ARW_CLR_SL_1P_X;
		static const float ARW_CLR_SL_2P_X;
		static const float ARW_CLR_SL_Y;

		//カラーセレクト番号表示
		static const float NUM_CLR_SL_1P_X;
		static const float NUM_CLR_SL_2P_X;
		static const float NUM_CLR_SL_Y;

		//操作 PLAYER/CPU
		static const uint32		PLAYER;
		static const uint32		CPU;
#pragma endregion

	};


	using P_ChSl_Pl = std::shared_ptr < _CharaSele_Player >;
	using WP_ChSl_Pl = std::weak_ptr < _CharaSele_Player >;


}	//namespace GAME


