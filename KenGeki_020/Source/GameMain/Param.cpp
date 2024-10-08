//=================================================================================================
//
// シーンパラメータ ソース
//		シーン間の共通で用いる値
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Param.h"
#include "LoadCharaBin_s3d.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Param::Param ()
	{
		//ゲーム設定ファイル開始
		m_setting.Load ();

		m_chara_name_1p = m_setting.GetName1p ();
		m_chara_name_2p = m_setting.GetName2p ();

	}

	//コピーコンストラクタ
	Param::Param ( const Param & rhs )
	{
		m_setting = rhs.m_setting;
	}

	Param::~Param ()
	{
	}

	void Param::LoadCharaData_All ()
	{
		//キャラ事前読込
		m_pChara_Ouka = GetpChara_Ouka ();
		m_pChara_Sae = GetpChara_Sae ();
		m_pChara_Retsudou = GetpChara_Retsudou ();
//		m_pChara_Retsudou_2 = GetpChara_Retsudou2 ();

		m_read_chara = T;
	}

	void Param::SetMutchMode ( MUTCH_MODE mode )
	{
		m_mutchMode = mode; 

		switch ( mode )
		{
		case MODE_PLAYER_PLAYER:	m_setting.SetPlayerMode ( MODE_PLAYER, MODE_PLAYER );	break;
		case MODE_PLAYER_CPU:		m_setting.SetPlayerMode ( MODE_PLAYER, MODE_CPU );	break;
		case MODE_CPU_PLAYER:		m_setting.SetPlayerMode ( MODE_CPU, MODE_PLAYER );	break;
		case MODE_CPU_CPU:			m_setting.SetPlayerMode ( MODE_CPU, MODE_CPU );	break;
		case MODE_PLAYER_NETWORK:	m_setting.SetPlayerMode ( MODE_PLAYER, MODE_NETWORK );	break;
		}
	}

	void Param::SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p )
	{
		if ( MODE_PLAYER == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_PLAYER_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_PLAYER_CPU; }
			if ( MODE_NETWORK == mode2p ) { m_mutchMode = MODE_PLAYER_NETWORK; }
		}
		else if ( MODE_CPU == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_CPU_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_CPU_CPU; }
		}
	}

	PLAYER_MODE Param::GetPlayerMode ( PLAYER_ID id ) const
	{
		PLAYER_MODE pm = MODE_PLAYER;
		if ( id == PLAYER_ID_1 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_PLAYER:		pm = MODE_CPU;	  	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_PLAYER; 	break;
			default: break;
			}
		}
		if ( id == PLAYER_ID_2 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_CPU;	  	break;
			case MODE_CPU_PLAYER:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_NETWORK; 	break;
			default: break;
			}
		}
		return pm;
	}

	void Param::SetRandomChara ()
	{
	}


	P_Chara Param::GetpChara_Ouka ()
	{
		if ( m_pChara_Ouka == nullptr )
		{
			m_pChara_Ouka = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb_0 ( U"chara_Ouka_Bin.dat", * m_pChara_Ouka );
		}
		return m_pChara_Ouka;
	}

	P_Chara Param::GetpChara_Sae ()
	{
		if ( m_pChara_Sae == nullptr )
		{
			m_pChara_Sae = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb_1 ( U"chara_Sae_Bin.dat", * m_pChara_Sae );
		}
		return m_pChara_Sae;
	}

	P_Chara Param::GetpChara_Retsudou ()
	{
		if ( m_pChara_Retsudou == nullptr )
		{
			m_pChara_Retsudou = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb_1 ( U"chara_Retsudou_Bin.dat", * m_pChara_Retsudou );
		}
		return m_pChara_Retsudou;
	}

	P_Chara Param::GetpChara_Retsudou2 ()
	{
		m_pChara_Retsudou_2 = std::make_shared < Chara > ();	//キャラデータ実体
		//		LoadCharaBin_s3d lcb_3 ( U"chara_Retsudou_Bin.dat", * m_pChara_Retsudou_2 );
		return m_pChara_Retsudou_2;
	}

}	//namespace GAME

