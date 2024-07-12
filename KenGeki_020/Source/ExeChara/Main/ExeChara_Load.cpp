//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	ロード関連 内部関数
	//================================================

	//シーンパラメータ関連初期化
	void ExeChara::ParamInit ( P_Param pParam )
	{
		//表示
		m_dispChara->ParamInit ( pParam );

		//入力 (プレイヤモードによる分岐)
		LoadInput ();

#if 0
		//ゲーム設定
		GameSettingFile stg = pParam->GetGameSetting ();

		//選択キャラ名前・モードを取得
//		m_name = stg.GetName ( m_playerID );
		m_name = pParam->GetCharaName ( m_playerID );
		m_playerMode = stg.GetPlayerMode ( m_playerID );

#endif // 0
	}

	//------------------------
	//読込
	void ExeChara::Load ()
	{
		//--------------------------------------------
		//m_pCharaのデータ読込
		LoadCharaData ();

		//--------------------------------------------
		//アクタ・ステートに用いる状態パラメータに登録
		m_actor.SetwpExeChara ( shared_from_this () );

		//--------------------------------------------
		//キャラ表示初期化
		m_dispChara->SetpChara ( m_pChara );
		m_dispChara->SetpCharaRect ( m_charaRect );

		//--------------------------------------------
		//バトルパラメータに設定
		m_btlPrm.SetpChara ( m_pChara );
		m_btlPrm.SetwpExeChara ( shared_from_this (), m_pOther );

#if 0
		//--------------------------------------------
		//エフェクト生成ベクタの生成
		m_oprtEf->MakeEfList ( m_pChara );

#endif // 0

		TASK_VEC::Load ();
	}

	//------------------------
	//初期化(複数回実行可能)
	void ExeChara::Init ()
	{
		//アクション・スクリプト初期化
		m_actionID = 0;
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_frame = 0;
		m_pScript = m_pAction->GetpScript ( m_frame );

		//バトルパラメータ
		m_btlPrm.Init ();
		SetParamFromScript ();	//スクリプトからパラメータを反映する

		//アクタ
		m_actor.Init ();

		//表示
		//@info Move()中のTransit()の後に遷移し、
		//	再度Move()は呼ばれず(Init()は呼ばれる)、
		//	Draw()が呼ばれるため、ここで手動の初期化が必要
		m_dispChara->Update ( m_pAction, m_pScript, m_btlPrm, m_pCharaInput );


#if 0
		//枠
		m_charaRect->ResetAllRect ();

		//スロウタイマ
		m_tmrSlow.Init ();

#endif // 0

		TASK_VEC::Init ();
	}

	//再設定
	void ExeChara::Reset ()
	{
		_Reset ();	//復旧時

		TASK_VEC::Reset ();
	}

	//------------------------
	//復旧時の再設定
	void ExeChara::_Reset ()
	{
#if 0

		//テクスチャメモリ確保関連は再設定
		Rele ();
		m_pChara = make_shared < Chara > ();
		Load ();
		m_dispChara->SetpChara ( m_pChara );
		m_oprtEf->MakeEfList ( m_pChara );

		//アクション・スクリプト再取得
		m_pAction = m_pChara->GetpAction ( m_actionID );
		m_pScript = m_pAction->GetpScript ( m_frame );

		//表示の更新
		m_dispChara->Update ( m_pAction, m_pScript, m_btlPrm, m_pCharaInput );

		//エフェクト 表示のみ
		m_oprtEf->Disp ();

#endif // 0
	}

	void ExeChara::LoadCharaData ()
	{
		//--------------------------------------------
		//m_pCharaのデータ読込

		//名前からスクリプトファイルを指定してキャラのロード
		s3d::String name ( U"chara_Stand_Bin.dat" );

		//名前の指定
		PLAYER_ID id = m_btlPrm.GetPlayerID ();
		if ( PLAYER_ID_1 == id )
		{
//			name.assign ( _T ( "charaBin.dat" ) );
//			name.assign ( U"chara_Stand_Bin.dat" );
			name.assign ( U"chara_Sae_Bin.dat" );
//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}
		else if ( PLAYER_ID_2 == id )
		{
//			name.assign ( _T ( "charaBin.dat" ) );
//			name.assign ( U"chara_Stand_Bin.dat" );
			name.assign ( U"chara_Sae_Bin.dat" );
//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}

		//@info　キャラが複数に渡るとき、リアクション技指定をIDでなく名前で指定しないと位置がずれる

#if 0
		//パラメータによるキャラの選択
		switch ( m_name )
		{
//		case CHARA_OUKA: name.assign ( _T ( "Ouka.dat" ) ); break;
//		case CHARA_SAE : name.assign ( _T ( "Sae.dat" ) ); break;
		case CHARA_OUKA: name.assign ( _T ( "charaBin.dat" ) ); break;
		case CHARA_SAE : name.assign ( _T ( "chara_Sae_Bin.dat" ) ); break;
		default: break;
		}
#endif // 0

		//キャラデータ読込
		if ( PLAYER_ID_1  == id )
		{		
			//バイナリデータ読込
//			LoadCharaBin loadCharaBin ( name.c_str (), *m_pChara );
			LoadCharaBin_s3d loadCharaBin ( name, * m_pChara );
		}
		else if ( PLAYER_ID_2  == id )
		{
			//1pと2pで名前が同じとき、既に読み込んであるキャラデータを参照する
			if ( this->m_name == m_pOther.lock()->m_name )
			{
				m_pChara = m_pOther.lock()->m_pChara;
			}
		}
	}


	void ExeChara::LoadInput ()
	{
		//キャラ入力(プレイヤー, CPU, Network)
		m_pPlayerInput = std::make_shared < PlayerInput > ();
		m_pPlayerInput->SetPlayer ( m_btlPrm.GetPlayerID () );

#if 0
		m_pCPUInput = std::make_shared < CPUInput > ( shared_from_this (), m_pOther );
		m_pCPUInput->SetPlayer ( m_playerID );
		m_pCPUInput->Load ();
#endif // 0

#if 0
		//プレイヤモード(入力種類)による初期化
		switch ( m_playerMode )
		{
		case MODE_PLAYER: m_pCharaInput = m_pPlayerInput; break;
		case MODE_CPU: m_pCharaInput = m_pCPUInput; break;
		case MODE_NETWORK: m_pCharaInput = m_pPlayerInput; break;	//(仮)
		default: break;
		}
#endif // 0
		m_pCharaInput = m_pPlayerInput;
	}

}	//namespace GAME

