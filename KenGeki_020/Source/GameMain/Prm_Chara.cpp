//=================================================================================================
//
//	Prm_Chara
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Prm_Chara.h"
#include "LoadCharaBin_s3d.h"
#include "LoadImgFile.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region FILE_NAME

	//キャラメインデータファイル scp
	constexpr char32_t CHARA_DAT_OUKA []	= U"chara_Ouka.scp";
	constexpr char32_t CHARA_DAT_SAE []		= U"chara_Sae.scp";
	constexpr char32_t CHARA_DAT_RETSU []	= U"chara_Retsudou.scp";
	constexpr char32_t CHARA_DAT_GABA []	= U"chara_Gabadaruga.scp";

	//キャライメージファイル img
	constexpr char32_t CHARA_IMG1_OUKA []	= U"chara_Ouka_bhv.lz4";
	constexpr char32_t CHARA_IMG2_OUKA []	= U"chara_Ouka_2p_bhv.lz4";
	constexpr char32_t CHARA_IMG1_SAE []	= U"chara_Sae_bhv.lz4";
	constexpr char32_t CHARA_IMG2_SAE []	= U"chara_Sae_bhv.lz4";
	constexpr char32_t CHARA_IMG1_RETSU []	= U"chara_Retsudou_bhv.lz4";
	constexpr char32_t CHARA_IMG2_RETSU []	= U"chara_Retsudou_2p_bhv.lz4";
	constexpr char32_t CHARA_IMG1_GABA []	= U"chara_Gabadaruga_bhv.lz4";
	constexpr char32_t CHARA_IMG2_GABA []	= U"chara_Gabadaruga_bhv.lz4";

	//キャラエフェクトイメージファイル
	constexpr char32_t CHARA_GNS_OUKA []	= U"chara_Ouka_gns.lz4";
	constexpr char32_t CHARA_GNS_SAE []		= U"chara_Sae_gns.lz4";
	constexpr char32_t CHARA_GNS_RETSU []	= U"chara_Retsudou_gns.lz4";
	constexpr char32_t CHARA_GNS_GABA []	= U"chara_Gabadaruga_gns.lz4";

	//Chara_Color_File_Name
	struct CH_CLR_FL_NM
	{
		LPCUSTR clr1;
		LPCUSTR clr2;
	};

	LPCUSTR OUKA_clr[] { CHARA_IMG1_OUKA, CHARA_IMG2_OUKA };
	LPCUSTR SAE_clr[] { CHARA_IMG1_SAE, CHARA_IMG2_SAE };
	LPCUSTR RETSU_clr[] { CHARA_IMG1_RETSU, CHARA_IMG2_RETSU };
	LPCUSTR GABA_clr[] { CHARA_IMG1_GABA, CHARA_IMG2_GABA };


#pragma endregion


	Prm_Chara::Prm_Chara ()
	{
	}

	Prm_Chara::Prm_Chara ( const Prm_Chara & rhs )
	{
		m_pChara		= rhs.m_pChara;
		m_papTx_clr1	= rhs.m_papTx_clr1;
		m_papTx_clr2	= rhs.m_papTx_clr2;
		m_papTx_gns		= rhs.m_papTx_gns;
	}

	Prm_Chara::~Prm_Chara ()
	{
	}


	void Prm_Chara::Load ()
	{
		m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
		LoadCharaBin_s3d lcb;
		lcb.Load ( m_filename_scp, * m_pChara );

		LoadImgFile lif;
		m_papTx_clr1 = lif.LoadLz4_Bhv ( m_filename_img_1p );
		m_papTx_clr2 = lif.LoadLz4_Bhv ( m_filename_img_2p );

		m_pChara->SetpapTx_Main ( m_papTx_clr1 );
	}


	//個別キャラデータを取得 (未ロード時はロードしてから取得)
	P_Chara Prm_Chara::GetpChara ( CHARA_COLOR clr )
	{
		PRINT_F_S( U"スクリプト" );
		//スクリプト部
		if ( nullptr == m_pChara )
		{
			m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb;
			lcb.Load ( m_filename_scp, * m_pChara );
		}
		PRINT_F_S( U"OK\n" );


		PRINT_F_S( U"カラー" );
		//カラー別
		LoadImgFile lif;
		if ( CH_CLR_1 == clr )
		{
			if ( nullptr == m_papTx_clr1 )
			{
				m_papTx_clr1 = lif.LoadLz4_Bhv ( m_filename_img_1p );
			}
			m_pChara->SetpapTx_Main ( m_papTx_clr1 );
		}
		else if ( CH_CLR_2 == clr )
		{
			if ( nullptr == m_papTx_clr2 )
			{
				m_papTx_clr2 = lif.LoadLz4_Bhv ( m_filename_img_2p );
			}
			m_pChara->SetpapTx_Main ( m_papTx_clr2 );
		}
		PRINT_F_S( U"OK\n" );



		PRINT_F_S( U"エフェクト" );
		//共通エフェクト
		if ( nullptr == m_papTx_gns )
		{
			s3d::String fn ( m_filename_scp );
			m_papTx_gns = lif.LoadLz4_Gns ( m_filename_gns );
		}
		m_pChara->SetpapTx_Ef ( m_papTx_gns );
		PRINT_F_S( U"OK\n" );




		return m_pChara;
	}


	//-----------------------------------------

	Prm_Chara_all::Prm_Chara_all ()
	{
		m_Ouka.SetStrScp ( CHARA_DAT_OUKA );
		m_Ouka.SetStrImg_1p ( CHARA_IMG1_OUKA );
		m_Ouka.SetStrImg_2p ( CHARA_IMG2_OUKA );
		m_Ouka.SetStrGns ( CHARA_GNS_OUKA );

		m_Sae.SetStrScp ( CHARA_DAT_SAE );
		m_Sae.SetStrImg_1p ( CHARA_IMG1_SAE );
		m_Sae.SetStrImg_2p ( CHARA_IMG2_SAE );
		m_Sae.SetStrGns ( CHARA_GNS_SAE );

		m_Retsu.SetStrScp ( CHARA_DAT_RETSU );
		m_Retsu.SetStrImg_1p ( CHARA_IMG1_RETSU );
		m_Retsu.SetStrImg_2p ( CHARA_IMG2_RETSU );
		m_Retsu.SetStrGns ( CHARA_GNS_RETSU );

		m_Gaba.SetStrScp ( CHARA_DAT_GABA );
		m_Gaba.SetStrImg_1p ( CHARA_IMG1_GABA );
		m_Gaba.SetStrImg_2p ( CHARA_IMG2_GABA );
		m_Gaba.SetStrGns ( CHARA_GNS_GABA );
	}

	Prm_Chara_all::Prm_Chara_all ( const Prm_Chara_all & rhs )
	{
		m_Ouka = rhs.m_Ouka;
		m_Sae = rhs.m_Sae;
		m_Retsu = rhs.m_Retsu;
		m_Gaba = rhs.m_Gaba;
	}

	Prm_Chara_all::~Prm_Chara_all ()
	{
	}


		//すべて読込
	void Prm_Chara_all::LoadAll ()
	{
		m_Ouka.Load ();
		m_Sae.Load ();
		m_Retsu.Load ();
		m_Gaba.Load ();
	}


	//キャラ名とカラーからデータポインタを取得
	P_Chara Prm_Chara_all::GetpChara ( CHARA_NAME name, CHARA_COLOR clr )
	{
		switch ( name )
		{
		case CHARA_OUKA: return m_Ouka.GetpChara ( clr );
		case CHARA_SAE: return m_Sae.GetpChara ( clr );
		case CHARA_RETSUDOU: return m_Retsu.GetpChara ( clr );
		case CHARA_GABADARUGA: return m_Gaba.GetpChara ( clr );
		}

		return m_Ouka.GetpChara ( clr );
	}


}	//namespace GAME

