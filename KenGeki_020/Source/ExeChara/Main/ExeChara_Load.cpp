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

		//キャラ選択
		m_name = pParam->GetCharaName ( m_btlPrm.GetPlayerID () );

		//キャラ表示
		m_dispChara->ParamInit ( pParam );

		//入力 (プレイヤモードによる分岐)
		LoadInput ();

		//バトルパラメータ
		m_btlPrm.ParamInit ( pParam );

#if 0

		//ゲーム設定ファイル
		GameSettingFile stg = pParam->GetGameSetting ();

		//キャラ名

		if ( stg.GetDemo () )
		{
			//デモ時はランダム
			int rnd = s3d::Random ( 1 );
			switch ( rnd )
			{
			case 0: m_name = CHARA_NAME::CHARA_SAE;			break;
			case 1: m_name = CHARA_NAME::CHARA_RETSUDOU;	break;
			};

			//キャラを記録
			if ( Is1P () )
			{
				pParam->SetCharaName1p ( m_name );
			}
			else if ( Is2P () )
			{
				pParam->SetCharaName2p ( m_name );
			}
			stg.Save ();
		}
		else
		{
	//		m_name = stg.GetName ( m_playerID );
			m_name = pParam->GetCharaName ( m_btlPrm.GetPlayerID () );
	//		m_name = CHARA_SAE;
	//		m_name = CHARA_RETSUDOU;
		}

#endif // 0

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
		m_pActor->SetwpExeChara ( shared_from_this () );
		m_pActor->Load ();

		//--------------------------------------------
		//キャラ表示初期化
		m_dispChara->SetpChara ( m_pChara );
		m_dispChara->SetpCharaRect ( m_charaRect );

		//--------------------------------------------
		//バトルパラメータに設定
		m_btlPrm.SetpChara ( m_pChara );
		m_btlPrm.SetwpExeChara ( shared_from_this (), m_pOther );

		//相殺キャンセルリストを先に作成しておく
		MakeOfstCnclList ();

		//--------------------------------------------
		//エフェクト生成ベクタの生成
		m_oprtEf->MakeEfList ( m_pChara );

		//--------------------------------------------
		TASK_VEC::Load ();


#if 0

		TRACE_F ( _T("\n\n\n\n\n") );
		TRACE_F ( _T("■■■■■■■■■■■■■■■■■■■■■■■■\n") );
		TRACE_F ( _T("■■■■■■■■■■■■■■■■■■■■■■■■\n") );
		TRACE_F ( _T("■■■■■■■■■■■■■■■■■■■■■■■■\n") );

		int count = 0;
		for ( P_Action pAct : * m_pChara->GetpvpAction () )
		{
			for ( P_Script pScp : * pAct->GetpvpScript () )
			{
				s3d::String se_name = pScp->m_prmStaging.SE_Name;
				if ( 0 != se_name.compare ( U"" ) )
				{
					TRACE_F ( _T("%s\n"), pScp->m_prmStaging.SE_Name.toWstr().c_str() );
				}
				++ count;
			}
		}
		TRACE_F ( _T("%d\n"), count );

#endif // 0
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

		//入力
		m_pCharaInput->ClearInput ();

		//遷移
		m_nameChangeMine = U"ノーリアクション";
		m_nameChangeOther = U"ノーリアクション";

		//アクタ
		m_pActor->Init ();

		//表示
		// 特殊演出初期化
		m_dispChara->TurnShadow ( F );
		
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
		s3d::String filename ( U"chara_Stand_Bin.dat" );

		PLAYER_ID id = m_btlPrm.GetPlayerID ();

#if 0
		//[test] 名前の直接指定
		if ( PLAYER_ID_1 == id )
		{
			//			name.assign ( U"charaBin.dat" );
			filename.assign ( U"chara_Ouka_Bin.dat" );		m_name = CHARA_OUKA;
			//			name.assign ( U"chara_Sae_Bin.dat" );		m_name = CHARA_SAE;
			//			name.assign ( U"chara_Retsudou_Bin.dat" );		m_name = CHARA_RETSUDOU;
			//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}
		else if ( PLAYER_ID_2 == id )
		{
			//			name.assign ( _T ( "charaBin.dat" ) );
			//			name.assign ( U".dat" );		m_name = CHARA_OUKA;
			filename.assign ( U"chara_Sae_Bin.dat" );		m_name = CHARA_SAE;
			//			name.assign ( U"chara_Retsudou_Bin.dat" );		m_name = CHARA_RETSUDOU;
			//			name.assign ( _T ( "chara_E0_Bin.dat" ) );
		}
#endif // 0


		//@info　キャラが複数に渡るとき、リアクション技指定をIDでなく名前で指定しないと位置がずれる


		//パラメータによるキャラの選択
		switch ( m_name )
		{
		case CHARA_OUKA:		filename.assign ( U"chara_Ouka_Bin1.dat" ); break;
		case CHARA_SAE:			filename.assign ( U"chara_Sae_Bin1.dat" ); break;
		case CHARA_RETSUDOU:	filename.assign ( U"chara_Retsudou_Bin1.dat" ); break;
//		case CHARA_GABADARUGA:	filename.assign ( U"charaBin.dat" ); break;
		default: break;
		}

		//キャラデータ読込
		if ( PLAYER_ID_1  == id )
		{		
			//バイナリデータ読込
			LoadCharaBin_s3d loadCharaBin ( filename, * m_pChara );
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
				LoadCharaBin_s3d loadCharaBin ( filename, * m_pChara );
			}
		}

	}


	void ExeChara::LoadCharaData ()
	{
		//--------------------------------------------
		//m_pCharaのデータ読込

#if 0

		PLAYER_ID id = GetPlayerID ();

		//パラメータによるキャラの選択
		switch ( m_name )
		{
		case CHARA_OUKA:		m_pChara = m_pParam->GetpChara_Ouka ( id );		break;
		case CHARA_SAE:			m_pChara = m_pParam->GetpChara_Sae ( id );		 break;
		case CHARA_RETSUDOU:	m_pChara = m_pParam->GetpChara_Retsudou ( id );	 break;
		case CHARA_GABADARUGA:	m_pChara = m_pParam->GetpChara_Gabadaruga ( id );	 break;
		default: break;
		}

#endif // 0

		//パラメータによるキャラの選択
		switch ( m_name )
		{
		case CHARA_OUKA:		m_pChara = m_pParam->GetpChara_Ouka (  );		break;
		case CHARA_SAE:			m_pChara = m_pParam->GetpChara_Sae (  );		 break;
		case CHARA_RETSUDOU:	m_pChara = m_pParam->GetpChara_Retsudou (  );	 break;
		case CHARA_GABADARUGA:	m_pChara = m_pParam->GetpChara_Gabadaruga (  );	 break;
		default: break;
		}

	}


	void ExeChara::LoadInput ()
	{
		//キャラ入力(プレイヤー, CPU, Network)
		//初期化
		m_pPlayerInput = std::make_shared < PlayerInput > ();
		m_pPlayerInput->SetPlayer ( m_btlPrm.GetPlayerID () );

		m_pCPUInput = std::make_shared < CPUInput > ( shared_from_this (), m_pOther );
		m_pCPUInput->SetPlayer ( m_btlPrm.GetPlayerID () );
		m_pCPUInput->Load ();

		m_pNewCPUInput = std::make_shared < NewCPUInput > ();
		m_pNewCPUInput->SetPlayer ( m_btlPrm.GetPlayerID () );


		//設定ファイルからモードを取得
		GameSettingFile stg = m_pParam->GetGameSetting ();
		m_playerMode = stg.GetPlayerMode ( m_btlPrm.GetPlayerID () );

		//プレイヤモード(入力種類)による初期化
		switch ( m_playerMode )
		{
		case MODE_PLAYER: m_pCharaInput = m_pPlayerInput; break;
//		case MODE_CPU: m_pCharaInput = m_pCPUInput; break;
		case MODE_CPU: m_pCharaInput = m_pNewCPUInput; break;
//		case MODE_NETWORK: m_pCharaInput = m_pPlayerInput; break;	//(仮)
		default: break;
		}

//		m_pCharaInput = m_pPlayerInput;
	}



	//相殺キャンセルリスト生成
	void ExeChara::MakeOfstCnclList ()
	{
		//移動、通常、必殺、超必殺でキャンセル可能
		
		//@info コマンドかつ移動だと前離しによる移動停止でニュートラルなどが含まれるので外す
		//優先順位
		//地上・空中分岐

		//キャラからルートリストを取得
		const VP_Route vpRoute = m_pChara->GetvpRoute ();
		const VP_Branch vpBrc = m_pChara->GetvpBranch ();


		//地上
		m_vOfstCncl.clear ();
		UINT32 i = 0;
		for ( P_Route pRut : vpRoute )
		{
			if ( 0 == pRut->GetName ().compare ( U"地上超必殺技" ) )
			{
				const V_UINT vBrc = pRut->GetcvIDBranch ();

				//手動でリストに追加
				for ( UINT32 iBrc : vBrc )
				{
					m_vOfstCncl.push_back ( iBrc );
				}
			}

			++ i;
		}

		//空中
		m_vOfstCncl_Air.clear ();
		UINT32 i_air = 0;
		for ( P_Branch pBrc : vpBrc )
		{
			//条件：空中行動可能アクションのみ
			//現在は不可
#if 0
			//条件：コマンド入力のみ
			if ( BRC_CMD == pBrc->GetCondition () )
			{
				//リストに追加
				m_vOfstCncl_Air.push_back ( i_air );
			}

#endif // 0


			++ i_air;
		}
	}



}	//namespace GAME

