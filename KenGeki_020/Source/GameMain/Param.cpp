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
#include "../FtgMain/FtgConst.h"
#include "LoadImgFile.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region FILE_NAME

	//キャラメインデータファイル
	constexpr char32_t CHARA_DAT_OUKA []		= U"chara_Ouka.dat";
	constexpr char32_t CHARA_DAT_SAE []			= U"chara_Sae.dat";
	constexpr char32_t CHARA_DAT_RETSUDOU []	= U"chara_Retsudou.dat";
	constexpr char32_t CHARA_DAT_GABADARUGA []	= U"chara_Gabadaruga.dat";

	//キャライメージファイル
	constexpr char32_t CHARA_IMG1_OUKA []		= U"chara_Ouka_bhv.lz4";
	constexpr char32_t CHARA_IMG2_OUKA []		= U"chara_Ouka_bhv.lz4";
	constexpr char32_t CHARA_IMG1_SAE []		= U"chara_Sae_bhv.lz4";
	constexpr char32_t CHARA_IMG2_SAE []		= U"chara_Sae_bhv.lz4";
	constexpr char32_t CHARA_IMG1_RETSUDOU []	= U"chara_Retsudou_bhv.lz4";
	constexpr char32_t CHARA_IMG2_RETSUDOU []	= U"chara_Retsudou2p_bhv.lz4";
	constexpr char32_t CHARA_IMG1_GABADARUGA []	= U"chara_Gabadaruga_bhv.lz4";
	constexpr char32_t CHARA_IMG2_GABADARUGA []	= U"chara_Gabadaruga_bhv.lz4";

	//Chara_Color_File_Name
	struct CH_CLR_FL_NM
	{
		LPCUSTR clr1;
		LPCUSTR clr2;
	};

	LPCUSTR OUKA_clr[] { CHARA_IMG1_OUKA, CHARA_IMG2_OUKA };
	LPCUSTR SAE_clr[] { CHARA_IMG1_SAE, CHARA_IMG2_SAE };
	LPCUSTR RETSU_clr[] { CHARA_IMG1_RETSUDOU, CHARA_IMG2_RETSUDOU };
	LPCUSTR GABA_clr[] { CHARA_IMG1_GABADARUGA, CHARA_IMG2_GABADARUGA };


#pragma endregion


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
		m_pChara_Gabadaruga = GetpChara_Gabadaruga ();

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

	//-----------------------------------------------------------------
	//各キャラの読込
	//	タイトルから開始時は全キャラ先に読込
	//	テスト用バトルから開始時は各使用キャラのみ
	P_Chara Param::GetpChara_Ouka ()
	{
		if ( m_pChara_Ouka == nullptr )
		{
			m_pChara_Ouka = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb ( CHARA_DAT_OUKA, * m_pChara_Ouka );
		}
		return m_pChara_Ouka;
	}

	P_Chara Param::GetpChara_Ouka ( PLAYER_ID player )
	{
		P_Chara pCh = GetpChara_Ouka ();
		CHARA_NAME cn = CHARA_OUKA;
		SetImgClr ( pCh, cn, player );
		return pCh;
	}

	//-----------------------------------------------------------------
	P_Chara Param::GetpChara_Sae ()
	{
		if ( m_pChara_Sae == nullptr )
		{
			m_pChara_Sae = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb ( CHARA_DAT_SAE, * m_pChara_Sae );
		}
		return m_pChara_Sae;
	}

	P_Chara Param::GetpChara_Sae ( PLAYER_ID player )
	{
		P_Chara pCh = GetpChara_Sae ();
		CHARA_NAME cn = CHARA_SAE;
		SetImgClr ( pCh, cn, player );
		return pCh;
	}

	//-----------------------------------------------------------------
	P_Chara Param::GetpChara_Retsudou ()
	{
		if ( m_pChara_Retsudou == nullptr )
		{
			m_pChara_Retsudou = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb ( CHARA_DAT_RETSUDOU, * m_pChara_Retsudou );
		}
		return m_pChara_Retsudou;
	}

	P_Chara Param::GetpChara_Retsudou ( PLAYER_ID player )
	{
		P_Chara pCh = GetpChara_Retsudou ();
		CHARA_NAME cn = CHARA_RETSUDOU;
		SetImgClr ( pCh, cn, player );
		return pCh;
	}


	//-----------------------------------------------------------------
	P_Chara Param::GetpChara_Gabadaruga ()
	{
		if ( m_pChara_Gabadaruga == nullptr )
		{
			m_pChara_Gabadaruga = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb ( CHARA_DAT_GABADARUGA, * m_pChara_Gabadaruga );
		}
		return m_pChara_Gabadaruga;
	}

	P_Chara Param::GetpChara_Gabadaruga ( PLAYER_ID player )
	{
		P_Chara pCh = GetpChara_Gabadaruga ();
		CHARA_NAME cn = CHARA_GABADARUGA;
		SetImgClr ( pCh, cn, player );
		return pCh;
	}

	//-----------------------------------------------------------------
	//プレイヤ側でカラー番号を取得
	CHARA_COLOR Param::GetClr ( PLAYER_ID id ) const
	{
		//プレイヤ側でカラー番号を取得
		CHARA_COLOR clr = CH_CLR_1;
		if ( PLAYER_ID_1 == id )
		{
			clr = m_setting.GetColor1p ();
		}
		else if ( PLAYER_ID_2 == id  )
		{
			clr = m_setting.GetColor2p ();
		}
		return clr;
	}


	//キャラとプレイヤ側でカラー番号別テクスチャ配列の参照
	PAP_Tx & Param::GetPAP_Tx ( CHARA_NAME name, PLAYER_ID id )
	{
		CHARA_COLOR clr = GetClr ( id );

		switch ( name )
		{
		case CHARA_OUKA:
			if ( CH_CLR_1 == clr ) { return m_pCH_CLR_Ouka_1; }
			else if ( CH_CLR_2 == clr ) { return m_pCH_CLR_Ouka_2; }
		break;

		case CHARA_SAE:
			if ( CH_CLR_1 == clr ) { return m_pCH_CLR_Sae_1; }
			else if ( CH_CLR_2 == clr ) { return m_pCH_CLR_Sae_2; }
		break;

		case CHARA_RETSUDOU:
			if ( CH_CLR_1 == clr ) { return m_pCH_CLR_Retsu_1; }
			else if ( CH_CLR_2 == clr ) { return m_pCH_CLR_Retsu_2; }
		break;

		case CHARA_GABADARUGA:
			if ( CH_CLR_1 == clr ) { return m_pCH_CLR_Sae_1; }
			else if ( CH_CLR_2 == clr ) { return m_pCH_CLR_Sae_2; }
		break;
		}
		return m_pCH_CLR_Ouka_1;
	}

	//キャラ名とプレイヤ側とカラー番号で読込ファイル名を取得
	LPCUSTR Param::GetImgFileName ( CHARA_NAME name, PLAYER_ID id ) const
	{
		//プレイヤ側でカラー番号を取得
		CHARA_COLOR clr = GetClr ( id );

		//キャラ名で分岐
		LPCUSTR filename = OUKA_clr [ CH_CLR_1 ];
		switch ( name )
		{
		case CHARA_OUKA:		filename = OUKA_clr [ clr ];	break;
		case CHARA_SAE:			filename = SAE_clr [ clr ];	break;
		case CHARA_RETSUDOU:	filename = RETSU_clr [ clr ];	break;
		case CHARA_GABADARUGA:	filename = GABA_clr [ clr ];	break;
		}

		return filename;
	}

	//ファイル名とキャラポインタで、指定カラー番号のテクスチャ配列を設置
	void Param::SetImgClr ( P_Chara pch, CHARA_NAME name, PLAYER_ID id )
	{
		PAP_Tx & r_paptx = GetPAP_Tx ( name, id );
		LPCUSTR filename = GetImgFileName ( name, id );

		if ( r_paptx == nullptr )
		{
			LoadImgFile lif;
			PAP_Tx paptx = lif.LoadLz4_Bhv ( filename );
			r_paptx = paptx;

			s3d::String fn ( filename );
			s3d::String fn_gns = fn.substr ( 0, fn.length() - 8 ) + U"_gns.lz4";
			pch->SetpapTx_Ef ( lif.LoadLz4_Gns ( fn_gns ) );
		}
		pch->SetpapTx_Main ( r_paptx );
	}


	//-----------------------------------------------------------------
	void Param::ResetBattleParam ()
	{
		//リザルト用
		m_winner = PLAYER_ID_1;		//勝者
		m_n_life_1p = LIFE_START;	//残ライフ
		m_n_life_2p = LIFE_START;	//
		m_n_input_1p = 0;			//入力数
		m_n_input_2p = 0;			//
		m_n_act_1p = 0;				//アクション回数
		m_n_act_2p = 0;				//
		m_n_offset = 0;				//相殺数
		m_n_max_chain_1p = 0;		//連撃数
		m_n_max_chain_2p = 0;		//
		m_n_max_damege_1p = 0;		//最大連撃力
		m_n_max_damege_2p = 0;		//
	}

	//最大だったら更新する
	void Param::UpdateIfMAX_DMG ( PLAYER_ID id, int n )
	{
		if ( id == PLAYER_ID_1 )
		{
			if (m_n_max_damege_1p < n)
			{
				m_n_max_damege_1p = n;
			}
		}
		else if ( id == PLAYER_ID_2 )
		{
			if ( m_n_max_damege_2p < n )
			{
				m_n_max_damege_2p = n;
			}
		}
	}

	void Param::UpdateIfMax_Chain ( PLAYER_ID id, int n )
	{
		if ( id == PLAYER_ID_1 )
		{
			if (m_n_max_chain_1p < n)
			{
				m_n_max_chain_1p = n;
			}
		}
		else if ( id == PLAYER_ID_2 )
		{
			if ( m_n_max_chain_2p < n )
			{
				m_n_max_chain_2p = n;
			}
		}
	}


}	//namespace GAME

