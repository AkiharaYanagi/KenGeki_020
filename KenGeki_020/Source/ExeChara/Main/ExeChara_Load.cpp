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
		//保存
		m_pParam = pParam;

		//キャラ表示
		m_dispChara->ParamInit ( pParam );

		//入力 (プレイヤモードによる分岐)
		LoadInput ();


		//ゲーム設定ファイル
		GameSettingFile stg = pParam->GetGameSetting ();


		//選択キャラ名前・モードを取得
//		m_playerMode = stg.GetPlayerMode ( m_playerID );


//		m_name = stg.GetName ( m_playerID );
		m_name = pParam->GetCharaName ( m_btlPrm.GetPlayerID () );
//		m_name = CHARA_SAE;
//		m_name = CHARA_RETSUDOU;

	}

	//------------------------
	//読込
	void ExeChara::Load ()
	{
		//--------------------------------------------
		//m_pCharaのデータ読込
#if 0
		//ゲームパラメータで最初に読み込み済みかどうか
		if ( m_pParam->IsReadChara () )
		{
			LoadCharaData ();
		}
		else
		{
			LoadCharaData_test ();
		}
#endif // 0
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

		//--------------------------------------------
		//エフェクト生成ベクタの生成
		m_oprtEf->MakeEfList ( m_pChara );

		//--------------------------------------------
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


	void ExeChara::LoadCharaData_test ()
	{
		//名前からスクリプトファイルを指定してキャラのロード
		s3d::String name ( U"chara_Stand_Bin.dat" );

		PLAYER_ID id = m_btlPrm.GetPlayerID ();

		//[test] 名前の直接指定
		if ( PLAYER_ID_1 == id )
		{
			//			name.assign ( U"charaBin.dat" );
			name.assign ( U"chara_Ouka_Bin.dat" );		m_name = CHARA_OUKA;
			//			name.assign ( U"chara_Sae_Bin.dat" );		m_name = CHARA_SAE;
			//			name.assign ( U"chara_Retsudou_Bin.dat" );		m_name = CHARA_RETSUDOU;
			//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}
		else if ( PLAYER_ID_2 == id )
		{
			//			name.assign ( _T ( "charaBin.dat" ) );
			//			name.assign ( U".dat" );		m_name = CHARA_OUKA;
			name.assign ( U"chara_Sae_Bin.dat" );		m_name = CHARA_SAE;
			//			name.assign ( U"chara_Retsudou_Bin.dat" );		m_name = CHARA_RETSUDOU;
			//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}


		//@info　キャラが複数に渡るとき、リアクション技指定をIDでなく名前で指定しないと位置がずれる


		//パラメータによるキャラの選択
		switch ( m_name )
		{
		case CHARA_OUKA:		name.assign ( U"chara_Ouka_Bin.dat" ); break;
		case CHARA_SAE:			name.assign ( U"chara_Sae_Bin.dat" ); break;
		case CHARA_RETSUDOU:	name.assign ( U"chara_Retsudou_Bin.dat" ); break;
		case CHARA_GABADARUGA:	name.assign ( U"charaBin.dat" ); break;
		default: break;
		}

		//キャラデータ読込
		if ( PLAYER_ID_1  == id )
		{		
			//バイナリデータ読込
			LoadCharaBin_s3d loadCharaBin ( name, * m_pChara );
		}
		else if ( PLAYER_ID_2  == id )
		{
			//1pと2pで名前が同じとき、既に読み込んであるキャラデータを参照する
			if ( this->m_name == m_pOther.lock()->m_name )
			{
				m_pChara = m_pOther.lock()->m_pChara;
			}
			else
			{
				LoadCharaBin_s3d loadCharaBin ( name, * m_pChara );
			}
		}

	}


	void ExeChara::LoadCharaData ()
	{
		//--------------------------------------------
		//m_pCharaのデータ読込

		//パラメータによるキャラの選択
		switch ( m_name )
		{
		case CHARA_OUKA:		m_pChara = m_pParam->GetpChara_Ouka ();			break;
		case CHARA_SAE:			m_pChara = m_pParam->GetpChara_Sae ();			 break;
		case CHARA_RETSUDOU:	m_pChara = m_pParam->GetpChara_Retsudou ();		 break;
		case CHARA_GABADARUGA:	m_pChara = m_pParam->GetpChara_Retsudou2 ();		 break;
		default: break;
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

