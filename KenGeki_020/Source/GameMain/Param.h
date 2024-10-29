//=================================================================================================
//
// シーンパラメータ ヘッダ
//		シーン間の共通で用いる値
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "GameSettingFile.h"
//#include "SceneCommon.h"
#include "Chara.h"
#include "SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Param	: public GameParam
	{
		//ゲーム設定 ( 外部ファイル読込 )
		GameSettingFile		m_setting;

		//内部設定
		GAME_MODE		m_gameMode { MODE_TRAINING };
		MUTCH_MODE		m_mutchMode { MODE_PLAYER_PLAYER };
		CHARA_NAME		m_chara_name_1p { CHARA_TEST };
		CHARA_NAME		m_chara_name_2p { CHARA_TEST };
		STAGE_NAME		m_stage_name { STAGE_YUUHINO_HARA };

		//キャラ事前読込
		P_Chara			m_pChara_Ouka { nullptr };
		P_Chara			m_pChara_Sae { nullptr };
		P_Chara			m_pChara_Retsudou { nullptr };
		P_Chara			m_pChara_Retsudou_2 { nullptr };
		bool			m_read_chara { F };

		//リザルト用
		PLAYER_ID		m_winner { PLAYER_ID_1 };		//勝者
		int32		m_n_life_1p { 0 };		//残ライフ
		int32		m_n_life_2p { 0 };		//
		int32		m_n_input_1p { 0 };		//入力数
		int32		m_n_input_2p { 0 };		//
		int32		m_n_act_1p { 0 };		//アクション回数
		int32		m_n_act_2p { 0 };		//
		int32		m_n_offset { 0 };		//相殺数
		int32		m_n_max_chain_1p { 0 };		//連撃数
		int32		m_n_max_chain_2p { 0 };		//
		int32		m_n_max_damege_1p { 0 };		//最大連撃力
		int32		m_n_max_damege_2p { 0 };		//

	public:
		Param ();
		Param ( const Param & rhs );	//コピー可能
		~Param ();

		//ゲーム設定 ( 外部ファイル読込 )
		const GameSettingFile & GetGameSetting () const { return m_setting; }
		void SetSettingFile ( const GameSettingFile & stg ) { m_setting = stg; }

		//内部設定
		void SetGameMode ( GAME_MODE mode ) { m_gameMode = mode; }
		GAME_MODE GetGameMode () const { return m_gameMode; }

		void SetMutchMode ( MUTCH_MODE mode );
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		MUTCH_MODE GetMutchMode () const { return m_mutchMode; }

		PLAYER_MODE GetPlayerMode ( PLAYER_ID id ) const;

		void SetCharaName1p ( CHARA_NAME name )
		{
			m_setting.SetCharaName1p ( name );
			m_chara_name_1p = name;
		}
		CHARA_NAME GetCharaName1p () const { return m_chara_name_1p; }
		void SetCharaName2p ( CHARA_NAME name )
		{
			m_setting.SetCharaName2p ( name );
			m_chara_name_2p = name;
		}
		CHARA_NAME GetCharaName2p () const { return m_chara_name_2p; }
		CHARA_NAME GetCharaName ( PLAYER_ID id )
		{
			if ( PLAYER_ID_1 == id ) { return m_chara_name_1p; }
			else if ( PLAYER_ID_2 == id ) { return m_chara_name_2p; }
			return CHARA_TEST;
		}
		void SetRandomChara ();

		GET_SET ( STAGE_NAME, GetStageName, SetStageName, m_stage_name	)		//bgm

		BGM_ID Get_BGM_ID () { return m_setting.GetBGM_ID (); }
		void Set_BGM_ID ( BGM_ID id ) { m_setting.SetBGM_ID ( id ); }


		//データ事前読込1
		void LoadCharaData_All ();
		P_Chara GetpChara_Ouka ();
		P_Chara GetpChara_Sae ();
		P_Chara GetpChara_Retsudou ();
		P_Chara GetpChara_Retsudou2 ();
		bool IsReadChara () const { return m_read_chara; }


		//リザルト用
		void ResetBattleParam ();

		void SetWinner ( PLAYER_ID plr ) { m_winner = plr; }
		PLAYER_ID GetWinner () const { return m_winner; }

		void SetN_Life1p ( int n ) { m_n_life_1p = n; }
		int GetN_Life1p () const { return m_n_life_1p; }
		void SetN_Life2p ( int n ) { m_n_life_2p = n; }
		int GetN_Life2p () const { return m_n_life_2p; }

		void SetN_Input1p ( int n ) { m_n_input_1p = n; }
		int GetN_Input1p () const { return m_n_input_1p; }
		void SetN_Input2p ( int n ) { m_n_input_2p = n; }
		int GetN_Input2p () const { return m_n_input_2p; }

		void SetN_Act1p ( int n ) { m_n_act_1p = n; }
		int GetN_Act1p () const { return m_n_act_1p; }
		void SetN_Act2p ( int n ) { m_n_act_2p = n; }
		int GetN_Act2p () const { return m_n_act_2p; }

		GET_SET ( int, GetOffset, SetOffset, m_n_offset )	//相殺数
		void AddOffset ( int32 n ) { m_n_offset += n; }

		GET_SET ( int, Get_MAX_DMG_1P, Set_MAX_DMG_1P, m_n_max_damege_1p	)		//最大ダメージ
		GET_SET ( int, Get_MAX_DMG_2P, Set_MAX_DMG_2P, m_n_max_damege_2p	)		//最大ダメージ
		GET_SET ( int, Get_MAX_CHN_1P, Set_MAX_CHN_1P, m_n_max_chain_1p	)		//連撃数
		GET_SET ( int, Get_MAX_CHN_2P, Set_MAX_CHN_2P, m_n_max_chain_2p	)		//連撃数


	};

	using P_Param = std::shared_ptr < Param >;


}	//namespace GAME

