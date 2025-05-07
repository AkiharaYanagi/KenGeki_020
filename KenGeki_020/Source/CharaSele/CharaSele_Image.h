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
#include "../GameMain/GameConst.h"
#include "../GameMain/Param.h"
#include "CharaSeleConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_GridTx = std::shared_ptr < s3d::Grid < P_Tx > >;


	//共通テクスチャ
	class CharaSele_Image_Common : public TASK_VEC
	{
		//パディング用
		P_Tx	m_tx_Pad;

		//キャラ立絵
		P_Tx	m_tx_Ouka;	
		P_Tx	m_tx_Sae;	
		P_Tx	m_tx_Retsu;	
		P_Tx	m_tx_Gaba;

		P_GridTx	m_gridTx;		//テクスチャグリッド

		//キャラ名前
		P_Tx	m_tx_name_Ouka;	
		P_Tx	m_tx_name_Sae;	
		P_Tx	m_tx_name_Retsu;	
		P_Tx	m_tx_name_Gaba;

	public:
		CharaSele_Image_Common ();
		CharaSele_Image_Common ( const CharaSele_Image_Common & rhs ) = delete;
		~CharaSele_Image_Common ();

		P_GridTx GetpGridTx () const { return m_gridTx; }

		P_Tx GetpTx_Pad () const { return m_tx_Pad; }

		P_Tx GetpTx_Ouka () const { return m_tx_Ouka; }
		P_Tx GetpTx_Sae () const { return m_tx_Sae; }
		P_Tx GetpTx_Retsu () const { return m_tx_Retsu; }
		P_Tx GetpTx_Gaba () const { return m_tx_Gaba; }

		P_Tx GetpTx_Name_Ouka () const { return m_tx_name_Ouka; }
		P_Tx GetpTx_Name_Sae () const { return m_tx_name_Sae; }
		P_Tx GetpTx_Name_Retsu () const { return m_tx_name_Retsu; }
		P_Tx GetpTx_Name_Gaba () const { return m_tx_name_Gaba; }

		P_Tx GetpTx ( const s3d::String & filename );

		//定数内は範囲保証
		P_Tx GetpTx ( CHARA_SELE_ID id, CHARA_COLOR clr );
		P_Tx GetpTx ( CHARA_NAME name, CHARA_COLOR clr );
	};

	using P_ChSl_Img_Cmn = std::shared_ptr < CharaSele_Image_Common >;


	class _CharaSele_Player;
	using P_ChSl_Pl = std::shared_ptr < _CharaSele_Player >;
	using WP_ChSl_Pl = std::weak_ptr < _CharaSele_Player >;



	//-----------------------------------------------------------
	class CharaSele_Image : public TASK_VEC
	{
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別

		CHARA_SELE_ID	m_chara_id { CHSLID_00 };	//選択キャラ
		CHARA_COLOR		m_chara_clr { CH_CLR_1 };	//選択カラー

		
		WP_ChSl_Pl		m_pOther;		//相手状態


		P_GridTx		m_gridTx;
		P_Grp			m_chara_stand;			//キャラ立絵
		P_Grp			m_chara_name;			//キャラ名前

		float			m_x { 0 };				//カットイン位置

		UINT32			m_waitDecide { 0 };		//決定時明度


	public:
		CharaSele_Image ();
		CharaSele_Image ( const CharaSele_Image & rhs ) = delete;
		~CharaSele_Image ();

		//参照
		void SetwpOther ( WP_ChSl_Pl pOther ) { m_pOther = pOther; }


		void LoadTx ( P_ChSl_Img_Cmn pCmn );
		void PlayerInit ( PLAYER_ID id );

		void Move ();



		//Selectは相手チェックが入るのでm_pOther設定後に用いる
		void SelectChara_cutin ( CHARA_SELE_ID id );
		void SelectChara ( CHARA_SELE_ID id );
		void SetChara ( CHARA_SELE_ID id );		//m_pOtherを用いない設置


		void SelectColor_cutin ( CHARA_COLOR clr );
		void SelectColor ( CHARA_COLOR clr );
		void SetColor ( CHARA_COLOR clr );		//m_pOtherを用いない設置


		void Decide ();

	private:
		void StartCutIn ();
		void HiddenCharaStand ();



#pragma region CONST
		//キャラ立ち絵
		static const float CHARA_1P_POS_X;
		static const float CHARA_1P_POS_Y;
		static const float CHARA_2P_POS_X;
		static const float CHARA_2P_POS_Y;
		static const float	CUTIN_X;
		static const float	CUTIN_VX;

		//キャラ名前
		static const float	CHARA_NAME_1P_X;
		static const float	CHARA_NAME_1P_Y;
		static const float	CHARA_NAME_2P_X;
		static const float	CHARA_NAME_2P_Y;

		static const float	POS0_X;
#pragma endregion

	};

	using P_ChSl_Img = std::shared_ptr < CharaSele_Image >;


}	//namespace GAME


