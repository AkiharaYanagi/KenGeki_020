//=================================================================================================
//
//	_CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "CharaSele_Image.h"
#include "_CharaSele_Player.h"
#include "CharaSele_Stage.h"
#include "CharaSele_BGM.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele : public Scene, public std::enable_shared_from_this < _CharaSele >
	{
		//-----------------------------------------------
		//キャラセレ　プレイヤ別処理
		P_ChSl_Pl		m_player_1p;
		P_ChSl_Pl		m_player_2p;


		//-----------------------------------------------
		//BG
		P_Grp			m_bg;
		P_Grp			m_charaFace;

		//Scroll
		P_Grp			m_scroll;
		float			m_scrl_y { 0 };

		//フェード (シーン移行フラグを兼ねる)
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
//		bool			m_endWait { F };
		uint32			m_plus_wait { 0 };


		//-----------------------------------------------
		//共有テクスチャ
		P_ChSl_Img_Cmn	m_img_cmn;

		//1P2P表示
		P_Grp			m_index_1p;
		P_Grp			m_index_2p;

		//文字表示
		P_GrpBlink		m_txt_CharacterSelect;	//キャラクターセレクト 
		P_GrpBlink		m_txt_BGMSelect;		//BGMセレクト

		//-----------------------------------------------
		//ステージセレクト
		P_CharaSele_Stage	m_stage;

		//BGMセレクト
		P_CharaSele_BGM		m_bgm;

		//-----------------------------------------------
		//OK表示
		P_Grp			m_OK;
		
		//操作説明
		P_Grp			m_inst;


	public:
		_CharaSele ();
		_CharaSele ( const _CharaSele & rhs ) = delete;
		~_CharaSele ();

		void ParamInit ();
		void Load ();
		void Move ();

		P_GameScene Transit ();


		//ステージ
		void Stage_On () { m_stage->On (); }
		void Stage_Prev () { m_stage->Prev (); }
		void Stage_Next () { m_stage->Next (); }
		void Stage_Decide () { m_stage->Decide (); }
		void Stage_Off () { m_stage->Off (); }

		//BGM
		void BGM_On () { m_bgm->On (); }
		void BGM_Prev () { m_bgm->Prev (); }
		void BGM_Next () { m_bgm->Next (); }
		void BGM_Decide () { m_bgm->Decide (); }
		void BGM_Off () { m_bgm->Off (); }

		//OK
		void OK_On_1p ();
		void OK_Off_1p ();
		void OK_On_2p ();
		void OK_Off_2p ();

		//-----------------------------------------------
		//文字表示グラフィックの作成
		static P_GrpBlink MakeTxtGrp ( VEC2 pos, const s3d::String & filename );


		//相手のキャラを取得
		CHARA_NAME GetOtherChara ( PLAYER_ID id );
		CHARA_COLOR GetOtherColor ( PLAYER_ID id );

	private:
		//内部関数
		void Save ();
		void Input ();
#pragma region CONST
		//位置
		static const float TXT_CHSL_X;
		static const float TXT_CHSL_Y;

		static const float CH_INDEX_X_1P;
		static const float CH_INDEX_X_2P;
		static const float CH_INDEX_Y;

		static const float CH_BAR_X_1P;
		static const float CH_BAR_X_2P;
		static const float CH_BAR_Y;

		//操作説明
		static const float INST_X;
		static const float INST_Y;

		//OK
		static const float OK_X_1P;
		static const float OK_X_2P;
		static const float OK_Y;

#pragma endregion
	};


	using WP_CharaSele = std::weak_ptr < _CharaSele >;


}	//namespace GAME

