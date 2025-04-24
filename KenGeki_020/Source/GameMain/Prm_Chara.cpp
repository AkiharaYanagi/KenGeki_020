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
	constexpr char32_t CHARA_DAT_OUKA []	= U"chara\\Ouka.scp";
	constexpr char32_t CHARA_DAT_SAE []		= U"Chara\\Sae.scp";
//	constexpr char32_t CHARA_DAT_SAE []		= U"Chara\\Feral.scp";
	constexpr char32_t CHARA_DAT_RETSU []	= U"Chara\\Retsudou.scp";
	constexpr char32_t CHARA_DAT_GABA []	= U"Chara\\Gabadaruga.scp";

	//キャライメージファイル img
	constexpr char32_t CHARA_IMG1_OUKA []	= U"Chara\\Ouka_1p_bhv.lz4";
//	constexpr char32_t CHARA_IMG2_OUKA []	= U"Chara\\Ouka_2p_bhv.lz4";
	constexpr char32_t CHARA_IMG2_OUKA []	= U"Chara\\Ouka_1p_bhv.lz4";

	constexpr char32_t CHARA_IMG1_SAE []	= U"Chara\\Sae_1p_bhv.lz4";
//	constexpr char32_t CHARA_IMG1_SAE []	= U"Chara\\Feral_bhv.lz4";
//	constexpr char32_t CHARA_IMG2_SAE []	= U"Chara\\Sae_2p_bhv.lz4";
	constexpr char32_t CHARA_IMG2_SAE []	= U"Chara\\Sae_1p_bhv.lz4";

	constexpr char32_t CHARA_IMG1_RETSU []	= U"Chara\\Retsudou_1p_bhv.lz4";
//	constexpr char32_t CHARA_IMG2_RETSU []	= U"Chara\\Retsudou_2p_bhv.lz4";
	constexpr char32_t CHARA_IMG2_RETSU []	= U"Chara\\Retsudou_1p_bhv.lz4";

	constexpr char32_t CHARA_IMG1_GABA []	= U"Chara\\Gabadaruga_1p_bhv.lz4";
	constexpr char32_t CHARA_IMG2_GABA []	= U"Chara\\Gabadaruga_1p_bhv.lz4";

	//キャラエフェクトイメージファイル
	constexpr char32_t CHARA_GNS_OUKA []	= U"Chara\\Ouka_gns.lz4";
	constexpr char32_t CHARA_GNS_SAE []		= U"Chara\\Sae_gns.lz4";
	constexpr char32_t CHARA_GNS_RETSU []	= U"Chara\\Retsudou_gns.lz4";
	constexpr char32_t CHARA_GNS_GABA []	= U"Chara\\Gabadaruga_gns.lz4";


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
		//既に読み込んでいる場合、何もしない
		if ( m_pChara != nullptr ) { return; }

		//---------------------------------------------------
		//スクリプト　
		m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
		LoadCharaBin_s3d lcb;
		lcb.Load ( m_filename_scp, * m_pChara );

		//---------------------------------------------------
		//カラー
		//ビヘイビア
		LoadImgFile lif;

		//1p
		m_papTx_clr1 = lif.LoadLz4_Bhv ( m_filename_img_1p );

		//2p
		//test
		//1p2p同じファイル名のとき既存データ利用
		s3d::String clr1 ( m_filename_img_1p );
		s3d::String clr2 ( m_filename_img_2p );
		if ( clr1 == clr2  )
		{
			m_papTx_clr2 = m_papTx_clr1;
		}
		else
		{
			m_papTx_clr2 = lif.LoadLz4_Bhv ( m_filename_img_2p );
		}

		//キャラに設置(初期値1p)
		m_pChara->SetpapTx_Main ( m_papTx_clr1 );

		//---------------------------------------------------
		//ガーニッシュ
		m_papTx_gns = lif.LoadLz4_Gns ( m_filename_gns );

		//キャラに設置(初期値1p)
		m_pChara->SetpapTx_Ef ( m_papTx_clr1 );
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
		//非同期タスク開放
#if 0
		if ( m_task.isValid () )
		{
			m_abort = true;
			m_task.wait ();
		}
#endif // 0

		if ( m_asyncLoad_Ouka.isValid () ) { m_asyncLoad_Ouka.wait (); }
		if ( m_asyncLoad_Sae_.isValid () ) { m_asyncLoad_Sae_.wait (); }
		if ( m_asyncLoad_Retu.isValid () ) { m_asyncLoad_Retu.wait (); }
		if ( m_asyncLoad_Gaba.isValid () ) { m_asyncLoad_Gaba.wait (); }

	}


	//すべて読込(非同期処理)
	void Prm_Chara_all::LoadAll ()
	{
		PRINT_F_S ( U"Prm_Chara_all::LoadAll\n" );

		m_asyncLoad_Ouka = s3d::Async ( _Load_Ouka, this );
		m_asyncLoad_Sae_ = s3d::Async ( _Load_Sae_, this );
		m_asyncLoad_Retu = s3d::Async ( _Load_Retu, this );
		m_asyncLoad_Gaba = s3d::Async ( _Load_Gaba, this );
	}

	//すべて読込(同期処理)
	void Prm_Chara_all::_LoadAll ()
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_LoadAll\n" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Ouka\n" );
		m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Ouka\n" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Sae_\n" );
		m_Sae.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Sae_\n" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Retu\n" );
		m_Retsu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Retu\n" );

//		m_Gaba.Load ();

		PRINT_F_S ( U"End Prm_Chara_all::_LoadAll\n" );
	}


	//すべて読込
	void Prm_Chara_all::_LoadAll ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_LoadAll\n" );
		pThis->m_Ouka.Load ();
		pThis->m_Sae.Load ();
		pThis->m_Retsu.Load ();
		pThis->m_Gaba.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_LoadAll\n" );
	}

	void Prm_Chara_all::_Load_Ouka ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Ouka\n" );
		pThis->m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Ouka\n" );
	}

	void Prm_Chara_all::_Load_Sae_ ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Sae_\n" );
		pThis->m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Sae_\n" );
	}

	void Prm_Chara_all::_Load_Retu ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Retu\n" );
		pThis->m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Retu\n" );
	}

	void Prm_Chara_all::_Load_Gaba ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Gaba\n" );
		pThis->m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Gaba\n" );
	}


	//キャラ名とカラーからデータポインタを取得
	P_Chara Prm_Chara_all::GetpChara ( CHARA_NAME name, CHARA_COLOR clr )
	{
		switch ( name )
		{
		case CHARA_OUKA:
			PRINT_F_S ( U"GetpChara ( CHARA_OUKA, CLR_{} )\n"_fmt((int32)clr) );
			if ( m_asyncLoad_Ouka.isValid () )
			{
				m_asyncLoad_Ouka.wait ();
			}
			return m_Ouka.GetpChara ( clr );
		case CHARA_SAE:
			PRINT_F_S ( U"GetpChara ( CHARA_SAE, CLR_{} )\n"_fmt((int32)clr) );
			if ( m_asyncLoad_Sae_.isValid () ) { m_asyncLoad_Sae_.wait (); }
			return m_Sae.GetpChara ( clr );
		case CHARA_RETSUDOU:
			PRINT_F_S ( U"GetpChara ( CHARA_RETSUDOU, CLR_{} )\n"_fmt((int32)clr) );
			if ( m_asyncLoad_Retu.isValid () ) { m_asyncLoad_Retu.wait (); }
			return m_Retsu.GetpChara ( clr );
		case CHARA_GABADARUGA:
			PRINT_F_S ( U"GetpChara ( CHARA_GABADARUGA, CLR_{} )\n"_fmt((int32)clr) );
			if ( m_asyncLoad_Gaba.isValid () ) { m_asyncLoad_Gaba.wait (); }
			return m_Gaba.GetpChara ( clr );
		}

		return m_Ouka.GetpChara ( clr );
	}


}	//namespace GAME

