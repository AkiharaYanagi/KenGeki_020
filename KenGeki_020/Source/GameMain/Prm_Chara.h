//=================================================================================================
//
//	パラメータ　キャラ
//		事前読込やカラー指定のため保持するポインタ類
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "Chara.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	
	//-----------------------------------------
	//キャラ個別データ
	class Prm_Chara
	{

		//ポインタのみ
		P_Chara		m_pChara { nullptr };

		//キャラカラー
		PAP_Tx		m_papTx_clr1 { nullptr };
		PAP_Tx		m_papTx_clr2 { nullptr };
		//共通エフェクト
		PAP_Tx		m_papTx_gns { nullptr };

		//スクリプトファイル名
		LPCUSTR		m_filename_scp { U"" };

		//イメージファイル名
		LPCUSTR		m_filename_img_1p { U"" };
		LPCUSTR		m_filename_img_2p { U"" };

		//エフェクトイメージファイル名
		LPCUSTR		m_filename_gns { U"" };

	public:
		Prm_Chara ();
		Prm_Chara ( const Prm_Chara & rhs );	//コピー可能
		~Prm_Chara ();

		//すべて読込
		void Load ();

		//スクリプトファイル名を設定
		void SetStrScp ( LPCUSTR pStr ) { m_filename_scp = pStr; }

		//イメージファイル名を設定
		void SetStrImg_1p ( LPCUSTR pStr ) { m_filename_img_1p = pStr; }
		void SetStrImg_2p ( LPCUSTR pStr ) { m_filename_img_2p = pStr; }

		//エフェクトイメージファイル名を設定
		void SetStrGns ( LPCUSTR pStr ) { m_filename_gns = pStr; }


		//個別キャラデータを取得 (未ロード時はロードしてから取得)
		P_Chara GetpChara ( CHARA_COLOR clr );
	};


	//-----------------------------------------
	//全キャラ分
	class Prm_Chara_all
	{
		//非同期処理
		s3d::AsyncTask < void >	m_asyncLoad_Ouka;
		s3d::AsyncTask < void >	m_asyncLoad_Sae_;
		s3d::AsyncTask < void >	m_asyncLoad_Retu;
		s3d::AsyncTask < void >	m_asyncLoad_Gaba;

		//終了ミューテックス
		std::mutex				m_mutex;

		//中断フラグ
		std::atomic < bool >	m_abort { F };


		//キャラデータ
		Prm_Chara		m_Ouka;
		Prm_Chara		m_Sae;
		Prm_Chara		m_Retsu;
		Prm_Chara		m_Gaba;

	public:
		Prm_Chara_all ();
		Prm_Chara_all ( const Prm_Chara_all & rhs );	//コピー可能
		~Prm_Chara_all ();


		//すべて読込
		void LoadAll ();

		//キャラ名とカラーからデータポインタを取得
		P_Chara GetpChara ( CHARA_NAME name, CHARA_COLOR clr );


	private:
		static void _LoadAll ( Prm_Chara_all * pThis );

		static void _Load_Ouka ( Prm_Chara_all * pThis );
		static void _Load_Sae_ ( Prm_Chara_all * pThis );
		static void _Load_Retu ( Prm_Chara_all * pThis );
		static void _Load_Gaba ( Prm_Chara_all * pThis );
	};


}	//namespace GAME

