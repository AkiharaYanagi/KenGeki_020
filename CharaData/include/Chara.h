//=================================================================================================
//
//	Chara ヘッダファイル
//		キャラクタのデータを管理する
//		イメージ、スクリプト、コマンド
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"

//GameLib_020 変更点　DirectXからSiv3Dに伴いテクスチャ定義が変更
#include "Define_Siv3D.h"

#include "Chara_Define.h"
#include "Chara_Const.h"
#include "Action.h"
#include "Effect.h"
#include "Behavior.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	キャラ 実行上データ ver 020
	//	
	//	キャラ	
	//		┣ビヘイビア
	//		┃	┣[]スクリプト
	//		┃		┣[]ルート
	//		┃		┣[]Efジェネレート
	//		┃
	//		┣ガーニッシュ
	//		┃	┣[]スクリプト
	//		┃		┣[]Efジェネレート
	//		┃
	//		┣[]コマンド
	//		┣[]ブランチ
	//		┣[]ルート
	//
	//==================================================================================


	class Chara
	{
//		Behavior		m_bhvMain;		//メイン スクリプト
//		PVP_TxBs		m_pvpTxMain;	//メインイメージ テクスチャ配列
//		PVP_Action		m_pvpAction;	//アクション配列
		PAP_Tx			mpap_txMain;	//メインイメージ テクスチャ配列
		PAP_Action		mpap_Action;	//アクション配列

//		Garnish			m_bhvEf;		//EF スクリプト
//		PVP_TxBs		m_pvpTxEf;		//EFイメージ テクスチャ配列
		PAP_Tx			mpap_txEf;		//EFイメージ テクスチャ配列
		PAP_Effect		mpap_Ef;		//エフェクト配列

		VP_Command		m_vpCommand;	//コマンド配列
		VP_Branch		m_vpBranch;		//ブランチ配列
		VP_Route		m_vpRoute;		//ルート配列

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Clear ();

		//-----------------------------------------------------------------
		//メインイメージ テクスチャ配列ポインタ
//		PVP_TxBs GetpvpMainTexture () const { return m_pvpTxMain; }
		PAP_Tx GetpapTxMain () const { return mpap_txMain; }

		//メインイメージ テクスチャ配列に追加
		void AddpMainTexture ( P_Tx pTexture ) { mpap_txMain->push_back ( pTexture ); }

		//メインイメージ テクスチャポインタの取得
		P_Tx GetpMainTexture ( UINT index ) { return mpap_txMain->at ( index ); }

		//-----------------------------------------------------------------
		//アクション配列ポインタを取得
//		PVP_Action GetpvpAction () { return m_pvpAction; }
		PAP_Action GetpvpAction () { return mpap_Action; }

		//アクション配列に追加
		void AddpAction ( P_Action pAction ) { mpap_Action->push_back ( pAction ); }

		//アクション配列にまとめて追加
		void AddpAction ( std::unique_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size );

		//---------------------------------------------------------------------
		//名前からアクションIDを取得する(無いときは０を返す)
		UINT GetActionID ( s3d::String name ) const;

		//アクションポインタを取得
		P_Action GetpAction ( UINT index ) { return mpap_Action->at ( index ); }
		P_Action GetpAction ( s3d::String name ) { return GetpAction ( GetActionID ( name ) ); }

		//---------------------------------------------------------------------
		//スクリプトポインタを取得
		P_Script GetpScript ( UINT indexAction, UINT indexScript ) { return mpap_Action->at ( indexAction )->GetpScript( indexScript ); }

		//次スクリプトが存在するかどうか
		bool IsNextScript ( UINT indexAction, UINT indexScript )
		{
			return mpap_Action->at ( indexAction )->IsNextScript( indexScript );
		}

		//-----------------------------------------------------------------
		//Efイメージ テクスチャ配列ポインタ
		PAP_Tx GetpvpEfTexture () const { return mpap_txEf; }

		//Efイメージ テクスチャ配列に追加
		void AddpEfTexture ( P_Tx pTexture ) { mpap_txEf->push_back ( pTexture ); }

		//エフェクト配列にまとめて追加
		void AddpEffect ( std::unique_ptr < P_Effect [] > arypEffect, rsize_t size );
		void AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size );

		//Efイメージ テクスチャポインタの取得
		P_Tx GetpEfTexture ( UINT index ) { return mpap_txEf->at ( index ); }

		//-----------------------------------------------------------------
		//エフェクト配列に追加
		void AddpEffect ( P_Effect pEffect ) { mpap_Ef->push_back ( pEffect ); }

		//エフェクト配列ポインタを取得
		PAP_Effect GetpvpEffect () { return mpap_Ef; }

		//エフェクトポインタを取得
		P_Effect GetpEffect ( UINT index ) { return mpap_Ef->at ( index ); }

		//---------------------------------------------------------------------
		//コマンド配列に追加
		void AddpCommand ( P_Command pCommand ) { m_vpCommand.push_back ( pCommand ); }
		void AddaCommand ( std::unique_ptr < P_Command [] > aryCmd, UINT size );

		//コマンドを取得
		P_Command GetpCommand ( UINT indexCommand ) const { return m_vpCommand[indexCommand]; }
		const VP_Command & GetvpCommand () const { return m_vpCommand; }


		//ブランチ配列に追加
		void AddpBranch ( P_Branch pBranch ) { m_vpBranch.push_back ( pBranch ); }
		void AddaBranch ( std::unique_ptr < P_Branch [] > aryBrc, UINT size );

		//ブランチを取得
		P_Branch GetpBranch ( UINT indexBranch ) const { return m_vpBranch[indexBranch]; }
		const VP_Branch & GetvpBranch () const { return m_vpBranch; }


		//ルート配列に追加
		void AddpRoute ( P_Route pRoute ) { m_vpRoute.push_back ( pRoute ); }
		void AddaRoute ( std::unique_ptr < P_Route [] > aryRut, UINT size );

		//ルートを取得
		P_Route GetpRoute ( UINT indexRoute ) const { return m_vpRoute[indexRoute]; }
		const VP_Route & GetvpRoute () const { return m_vpRoute; }
	};

	using P_Chara = std::shared_ptr < Chara >;
	using VP_Chara = std::vector < P_Chara >;
	using PVP_Chara = std::shared_ptr < VP_Chara >;


}	//namespace GAME


