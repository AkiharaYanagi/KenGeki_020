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
		//キャラ立絵
		m_tx_Ouka = GetpTx ( U"CharaSele\\Stand_Ouka.png" );
		m_tx_Pad = GetpTx ( U"16_16_Padding.png" );
		m_tx_Sae = GetpTx ( U"CharaSele\\Stand_Sae.png" );
		m_tx_Retsu = GetpTx ( U"CharaSele\\Stand_Retsudou.png" );
		m_tx_Gaba = GetpTx ( U"CharaSele\\Stand_Gabadaruga.png" );
	}

	CharaSele_Image_Common::~CharaSele_Image_Common ()
	{
	}


	P_Tx CharaSele_Image_Common::GetpTx ( const s3d::String & filename )
	{
		//アーカイブからファイルを取得
		ARCHIVE_FILE_USE file = ACVR()->GetFilePointer ( filename.toWstr().c_str() );

		if ( file.filePointer == nullptr )
		{
			//TRACE_F ( TEXT("アーカイブにファイルが見つかりませんでした\n") );
			return nullptr;
		}

		//メモリ上からテクスチャに変換
		s3d::MemoryReader mr ( (void*)(file.filePointer), file.fileSize );
		mr.setPos ( 0 );

		//テクスチャの作成
		P_Tx pTx = std::make_shared < s3d::Texture > ( std::move ( mr ) );

		return pTx;
	}


	//-----------------------------------------------------------
	CharaSele_Image::CharaSele_Image ()
	{
		//キャラ立絵
		m_chara_stand = std::make_shared < GameGraphic > ();
		AddpTask ( m_chara_stand );
		GRPLST_INSERT ( m_chara_stand );
	}

	CharaSele_Image::~CharaSele_Image ()
	{
	}

	void CharaSele_Image::LoadTx ( P_ChSl_Img_Cmn pCmn )
	{
		//テクスチャを追加
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Ouka () );
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Pad () );
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Sae () );
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Retsu () );
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Pad () );
		m_chara_stand->AddpTexture ( pCmn->GetpTx_Gaba () );
	}

	void CharaSele_Image::PlayerInit ( PLAYER_ID id )
	{
		m_player_id = id;

		if ( PLAYER_ID_1 == id )
		{
			m_x = CHARA_1P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_1P_POS_Y );
		}
		else if ( PLAYER_ID_2 == id )
		{
			m_x = CHARA_2P_POS_X;
			m_chara_stand->SetPos ( m_x, CHARA_2P_POS_Y );
		}

	}

}	//namespace GAME

