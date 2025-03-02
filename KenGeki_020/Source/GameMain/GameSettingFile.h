//=================================================================================================
//
// ゲーム設定ファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//ゲーム内設定
	class GameSettingFile
	{
		START_MODE		m_startMode { START_BATTLE };	//開始シーン指定
		bool			m_demo { F };			//デモモード(自動CPU_VS_CPU繰返)

		PLAYER_MODE		m_playerMode1p { MODE_PLAYER };	//１P操作
		PLAYER_MODE		m_playerMode2p { MODE_PLAYER };	//２P操作

		CHARA_NAME		m_name1p { CHARA_TEST };		//選択キャラ
		CHARA_NAME		m_name2p { CHARA_TEST };

		BGM_ID			m_bgm_id { BGM_ID_GABA };			//BGM_ID
		STAGE_NAME		m_stage_name { STAGE_YUUHINO_HARA };	//STAGE_NAME


	public:
		GameSettingFile ();
		GameSettingFile ( const GameSettingFile & rhs );	//コピー可能
		~GameSettingFile ();

		//読込
		void Load ();

		//保存
		void Save() const;

		//-----------------------------------------
		//値の取得

		//ゲームモード
		START_MODE GetStartMode () const { return m_startMode; }
	
		//プレイヤの種類
		PLAYER_MODE GetPlayerMode ( PLAYER_ID pid ) const
		{
			if ( pid == PLAYER_ID_1 ) { return m_playerMode1p; }
			if ( pid == PLAYER_ID_2 ) { return m_playerMode2p; }
			return MODE_PLAYER;
		}
		void SetPlayerMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p )
		{
			m_playerMode1p = mode1p;
			m_playerMode2p = mode2p;
		}
		PLAYER_MODE GetPlayerMode1p () const { return m_playerMode1p; }
		PLAYER_MODE GetPlayerMode2p () const { return m_playerMode2p; }
		void SetPlayerMode1p ( PLAYER_MODE mode ) { m_playerMode1p = mode; }
		void SetPlayerMode2p ( PLAYER_MODE mode ) { m_playerMode2p = mode; }

		//キャラ名
		CHARA_NAME GetName ( PLAYER_ID pid ) const
		{
			if ( pid == PLAYER_ID_1 ) { return m_name1p; }
			if ( pid == PLAYER_ID_2 ) { return m_name2p; }
			return CHARA_NAME_NUM;
		}
		CHARA_NAME GetName1p () const { return m_name1p; }
		CHARA_NAME GetName2p () const { return m_name2p; }
		void SetCharaName1p ( CHARA_NAME name ) { m_name1p = name; }
		void SetCharaName2p ( CHARA_NAME name ) { m_name2p = name; }

		//デモ (設定ファイルにも記録)
		GET_SET ( bool, GetDemo, SetDemo, m_demo )
		 
		//BGM
		GET_SET ( BGM_ID, GetBGM_ID, SetBGM_ID, m_bgm_id )
		 
		//Stage
		GET_SET ( STAGE_NAME, GetStage_Name, SetStage_Name, m_stage_name )
		 
		//-----------------------------------------

		//初期値
		void	SetDefault ();
	};

}	//namespace GAME

