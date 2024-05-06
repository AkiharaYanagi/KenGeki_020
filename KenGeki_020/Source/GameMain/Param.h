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
		MUTCH_MODE		m_mutchMode { MODE_PLAYER_PLAYER };
		CHARA_NAME		m_chara_name_1p { CHARA_TEST };
		CHARA_NAME		m_chara_name_2p { CHARA_TEST };

		//リザルト用
		PLAYER_ID		m_winner { _PLAYER_NUM };		//勝者
		int		m_n_life_1p { 0 };		//残ライフ
		int		m_n_life_2p { 0 };		//
		int		m_n_input_1p { 0 };		//入力数
		int		m_n_input_2p { 0 };		//
		int		m_n_act_1p { 0 };		//アクション回数
		int		m_n_act_2p { 0 };		//
		int		m_n_offset { 0 };		//相殺数

	public:
		Param ();
		Param ( const Param & rhs );	//コピー可能
		~Param ();

		//ゲーム設定 ( 外部ファイル読込 )
		GameSettingFile GetGameSetting () const { return m_setting; }
		void SetSettingFile ( GameSettingFile stg ) { m_setting = stg; }

		//内部設定
		void SetMutchMode ( MUTCH_MODE mode );
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		MUTCH_MODE GetMutchMode () const { return m_mutchMode; }

		PLAYER_MODE GetPlayerMode ( PLAYER_ID id ) const;

		void SetCharaName1p ( CHARA_NAME name ) { m_chara_name_1p = name; }
		CHARA_NAME GetCharaName1p () const { return m_chara_name_1p; }
		void SetCharaName2p ( CHARA_NAME name ) { m_chara_name_2p = name; }
		CHARA_NAME GetCharaName2p () const { return m_chara_name_2p; }
		CHARA_NAME GetCharaName ( PLAYER_ID id )
		{
			if ( PLAYER_ID_1 == id ) { return m_chara_name_1p; }
			else if ( PLAYER_ID_2 == id ) { return m_chara_name_2p; }
			return CHARA_TEST;
		}
		void SetRandomChara ();


		//リザルト用
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
	};

	using P_Param = std::shared_ptr < Param >;


}	//namespace GAME

