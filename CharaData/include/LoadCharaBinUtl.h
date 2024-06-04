//=================================================================================================
//
// LoadCharaBinUtl ヘッダファイル
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Chara.h"
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_CH = std::shared_ptr < char [] >;
	using P_BYTE = std::shared_ptr < byte [] >;
	using UP_BYTE = std::unique_ptr < byte [] >;
	using L_UINT = std::unique_ptr < UINT [] >;
	using CUPR_BYTE = const UP_BYTE &;

	//------------------------------------------------------------
	//	LoadCharaBinで用いる関数群
	//------------------------------------------------------------
	class LoadCharaBinUtl
	{
	public:
		LoadCharaBinUtl ();
		LoadCharaBinUtl ( const LoadCharaBinUtl & rhs ) = delete;
		~LoadCharaBinUtl () = default;

		//----
//		tstring LoadText ( UP_BYTE buf, UINT & pos );
		s3d::String LoadS3dString ( CUPR_BYTE buf, UINT & pos );
		bool LoadBool ( CUPR_BYTE buf, UINT & pos );
		byte LoadByte ( CUPR_BYTE buf, UINT & pos );
		int LoadInt ( CUPR_BYTE buf, UINT & pos );
		UINT LoadUInt ( CUPR_BYTE buf, UINT & pos );
		VEC2 LoadVec2 ( CUPR_BYTE buf, UINT & pos );
		VEC2 LoadVec2_Dev10F ( CUPR_BYTE buf, UINT & pos );
		RECT LoadRect ( CUPR_BYTE buf, UINT & pos );
		void LoadListRect ( CUPR_BYTE buf, UINT & pos, PV_RECT pvRect );
		L_UINT LoadAryUint ( CUPR_BYTE buf, UINT & pos, UINT & refLength );
		void LoadAryUint ( CUPR_BYTE buf, UINT & pos, V_UINT & refAryUint );
	};


}	//namespace GAME


