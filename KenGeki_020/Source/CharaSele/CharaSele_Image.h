//=================================================================================================
//
//	CharaSele Image ヘッダファイル
//		キャラ立ち絵管理
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSeleConst.h"
#include "../GameMain/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//共通テクスチャ
	class CharaSele_Image_Common : public TASK_VEC
	{
		//キャラ立絵
		P_Tx	m_tx_Ouka;	
		P_Tx	m_tx_Pad;	
		P_Tx	m_tx_Sae;	
		P_Tx	m_tx_Retsu;	
		P_Tx	m_tx_Pad4;
		P_Tx	m_tx_Gaba;

	public:
		CharaSele_Image_Common ();
		CharaSele_Image_Common ( const CharaSele_Image_Common & rhs ) = delete;
		~CharaSele_Image_Common ();

		P_Tx GetpTx_Ouka () const { return m_tx_Ouka; }
		P_Tx GetpTx_Pad () const { return m_tx_Pad; }
		P_Tx GetpTx_Sae () const { return m_tx_Sae; }
		P_Tx GetpTx_Retsu () const { return m_tx_Retsu; }
		P_Tx GetpTx_Gaba () const { return m_tx_Gaba; }

		P_Tx GetpTx ( const s3d::String & filename );

	};

	using P_ChSl_Img_Cmn = std::shared_ptr < CharaSele_Image_Common >;



	//-----------------------------------------------------------
	class CharaSele_Image : public TASK_VEC
	{
		P_Grp			m_chara_stand;			//キャラ立絵
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別

		float			m_x { 0 };				//カットイン位置



	public:
		CharaSele_Image ();
		CharaSele_Image ( const CharaSele_Image & rhs ) = delete;
		~CharaSele_Image ();

		void LoadTx ( P_ChSl_Img_Cmn pCmn );
		void PlayerInit ( PLAYER_ID id );

	private:
#pragma region CONST
		static constexpr float CHARA_1P_POS_X = -300;
		static constexpr float CHARA_1P_POS_Y = 50;
		static constexpr float CHARA_2P_POS_X = 500;
		static constexpr float CHARA_2P_POS_Y = 50;
#pragma endregion

	};

	using P_ChSl_Img = std::shared_ptr < CharaSele_Image >;


}	//namespace GAME


