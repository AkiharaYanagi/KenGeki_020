//=================================================================================================
//
//	CharaSele Image ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Image.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	CharaSele_Image_Common::CharaSele_Image_Common ()
	{
		//パディング用
		m_tx_Pad = GetpTx ( U"16_16_Padding.png" );

		//キャラ立絵
		m_tx_Ouka = GetpTx ( U"CharaSele\\Stand_Ouka.png" );
		m_tx_Sae = GetpTx ( U"CharaSele\\Stand_Sae.png" );
		m_tx_Retsu = GetpTx ( U"CharaSele\\Stand_Retsudou.png" );
		m_tx_Gaba = GetpTx ( U"CharaSele\\Stand_Gabadaruga.png" );

		//キャラ名前
		m_tx_name_Ouka = GetpTx ( U"CharaSele\\Name_Ouka.png" );
		m_tx_name_Sae = GetpTx ( U"CharaSele\\Name_Sae.png" );
		m_tx_name_Retsu = GetpTx ( U"CharaSele\\Name_Retsudou.png" );
		m_tx_name_Gaba = GetpTx ( U"CharaSele\\Name_Gabadaruga.png" );

		//テクスチャグリッド
		m_gridTx = std::make_shared < s3d::Grid < P_Tx > > ();
		m_gridTx->resize( CHARA_SELE_NUM, 2 );	//キャラ数 * 色数
		(*m_gridTx)[0][0] = GetpTx ( U"CharaSele\\Stand_Ouka.png" );
		(*m_gridTx)[1][0] = GetpTx ( U"CharaSele\\Stand_Ouka_2p.png" );
		(*m_gridTx)[0][1] = m_tx_Pad;
		(*m_gridTx)[1][1] = m_tx_Pad;
		(*m_gridTx)[0][2] = GetpTx ( U"CharaSele\\Stand_Sae.png" );
		(*m_gridTx)[1][2] = GetpTx ( U"CharaSele\\Stand_Sae_2p.png" );
		(*m_gridTx)[0][3] = GetpTx ( U"CharaSele\\Stand_Retsudou.png" );
		(*m_gridTx)[1][3] = GetpTx ( U"CharaSele\\Stand_Retsudou_2p.png" );
		(*m_gridTx)[0][4] = m_tx_Pad;
		(*m_gridTx)[1][4] = m_tx_Pad;
		(*m_gridTx)[0][5] = GetpTx ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][5] = GetpTx ( U"CharaSele\\Stand_Gabadaruga.png" );
	}

	CharaSele_Image_Common::~CharaSele_Image_Common ()
	{
	}

	inline P_Tx CharaSele_Image_Common::GetpTx ( const s3d::String & filename )
	{
		return TxUtl::MakeTx_FromArchive ( filename );
	}


	//-----------------------------------------------------------
	CharaSele_Image::CharaSele_Image ()
	{
		//キャラ立絵
		m_chara_stand = std::make_shared < GameGraphic > ();
		m_chara_stand->AddTexture ();
		AddpTask ( m_chara_stand );
		GRPLST_INSERT ( m_chara_stand );

		//キャラ名前
		m_chara_name = std::make_shared < GameGraphic > ();
		AddpTask ( m_chara_name );
		GRPLST_INSERT ( m_chara_name );
	}

	CharaSele_Image::~CharaSele_Image ()
	{
	}

	void CharaSele_Image::LoadTx ( P_ChSl_Img_Cmn pCmn )
	{
		//名前
		m_chara_name->AddpTexture ( pCmn->GetpTx_Name_Ouka () );
		m_chara_name->AddpTexture ( pCmn->GetpTx_Pad () );
		m_chara_name->AddpTexture ( pCmn->GetpTx_Name_Sae () );
		m_chara_name->AddpTexture ( pCmn->GetpTx_Name_Retsu () );
		m_chara_name->AddpTexture ( pCmn->GetpTx_Pad () );
		m_chara_name->AddpTexture ( pCmn->GetpTx_Name_Gaba () );


		//立ち絵初期指定
		m_gridTx = pCmn->GetpGridTx ();
		m_chara_clr = CH_CLR_1;
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_chara_id = CHSLID_00;
			m_chara_stand->AssignpTexture ( (*m_gridTx) [m_chara_clr][m_chara_id] );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_chara_id = CHSLID_02;
			m_chara_stand->AssignpTexture ( (*m_gridTx) [m_chara_clr][m_chara_id] );
		}
	}

	void CharaSele_Image::PlayerInit ( PLAYER_ID id )
	{
		m_player_id = id;

		if ( PLAYER_ID_1 == id )
		{
			m_x = CHARA_1P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
			m_chara_name->SetPos ( CHARA_NAME_1P_X, CHARA_NAME_1P_Y );
		}
		else if ( PLAYER_ID_2 == id )
		{
			m_x = CHARA_2P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
			m_chara_name->SetPos ( CHARA_NAME_2P_X, CHARA_NAME_2P_Y );
		}
	}

	void CharaSele_Image::Move ()
	{
		//選択カットイン
		if ( PLAYER_ID_1 == m_player_id )
		{
			if ( m_x < (int32)CHARA_1P_POS_X )
			{
				m_x += (int32)CUTIN_VX; 
				m_chara_stand->SetPos ( m_x, (float)CHARA_1P_POS_Y );
			}
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			if ( (int32)CHARA_2P_POS_X < m_x )
			{
				m_x -= (int32)CUTIN_VX; 
				m_chara_stand->SetPos ( m_x, (float)CHARA_2P_POS_Y );
			}
		}
	}

	void CharaSele_Image::SelectChara_cutin ( CHARA_SELE_ID chara_id )
	{
		//選択カットイン
		StartCutIn();

		//選択キャラ表示
		switch ( chara_id )
		{
		case CHSLID_00: SelectChara ( CHSLID_00 ); break;
		case CHSLID_01: HiddenCharaStand ();break;
		case CHSLID_02: SelectChara ( CHSLID_02 ); break;
		case CHSLID_03: SelectChara ( CHSLID_03 ); break;
		case CHSLID_04: HiddenCharaStand ();break;
		case CHSLID_05: HiddenCharaStand ();break;
		case CHSLID_06: HiddenCharaStand ();break;
		case CHSLID_07: HiddenCharaStand ();break;
		case CHSLID_08: HiddenCharaStand ();break;
		case CHSLID_09: HiddenCharaStand ();break;
		default: break;
		}

	}

	void CharaSele_Image::SelectChara ( CHARA_SELE_ID id )
	{
		if ( id == CHARA_SELE_NUM )
		{
			int i = 0;
			++ i;
		}


		m_chara_id = id;

		m_chara_stand->SetValid ( T );
		m_chara_stand->AssignpTexture ( (*m_gridTx) [m_chara_clr][id] );

		m_chara_name->SetValid ( T );
		m_chara_name->SetIndexTexture ( id );
	}


	//色を指定
	void CharaSele_Image::SetColor_cutin ( CHARA_COLOR clr )
	{
		//選択カットイン
		StartCutIn();

		//値を保存してテクスチャを指定
		m_chara_clr = clr;
		m_chara_stand->AssignpTexture ( (*m_gridTx) [clr][m_chara_id] );
	}

	void CharaSele_Image::SetColor ( CHARA_COLOR clr )
	{
		//値を保存してテクスチャを指定
		m_chara_clr = clr;
		m_chara_stand->AssignpTexture ( (*m_gridTx) [clr][m_chara_id] );
	}


	void CharaSele_Image::StartCutIn ()
	{
		if ( PLAYER_ID_1 == m_player_id )
		{
			m_x -= (float)CUTIN_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
		}
		else if ( PLAYER_ID_2 == m_player_id )
		{
			m_x += (float)CUTIN_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
		}
	}

	void CharaSele_Image::HiddenCharaStand ()
	{
		m_chara_stand->SetValid ( F ); 
		m_chara_name->SetValid ( F );
	}




#pragma region CONST
	//キャラ立ち絵
	const float	CharaSele_Image::CHARA_1P_POS_X = -300;
	const float	CharaSele_Image::CHARA_1P_POS_Y = 50;
	const float	CharaSele_Image::CHARA_2P_POS_X = 500;
	const float	CharaSele_Image::CHARA_2P_POS_Y = 50;

	const float	CharaSele_Image::CUTIN_X = 300;
	const float	CharaSele_Image::CUTIN_VX = 60;

	//キャラ名前
	const float	CharaSele_Image::CHARA_NAME_1P_X = -30 -10;
	const float	CharaSele_Image::CHARA_NAME_1P_Y = 400;
	const float	CharaSele_Image::CHARA_NAME_2P_X = 1280 + 30 - 256 - 10;
	const float	CharaSele_Image::CHARA_NAME_2P_Y = 400;

	const float	CharaSele_Image::POS0_X = 0;


#pragma endregion



}	//namespace GAME

