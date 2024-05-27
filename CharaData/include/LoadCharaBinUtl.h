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
		s3d::String LoadS3dString ( UP_BYTE buf, UINT & pos );
		bool LoadBool ( UP_BYTE buf, UINT & pos );
		byte LoadByte ( UP_BYTE buf, UINT & pos );
		int LoadInt ( UP_BYTE buf, UINT & pos );
		UINT LoadUInt ( UP_BYTE buf, UINT & pos );
		VEC2 LoadVec2 ( UP_BYTE buf, UINT & pos );
		VEC2 LoadVec2_Dev10F ( UP_BYTE buf, UINT & pos );
		RECT LoadRect ( UP_BYTE buf, UINT & pos );
		void LoadListRect ( UP_BYTE buf, UINT & pos, PV_RECT pvRect );
		L_UINT LoadAryUint ( UP_BYTE buf, UINT & pos, UINT & refLength );
		void LoadAryUint ( UP_BYTE buf, UINT & pos, V_UINT & refAryUint );
	};


}	//namespace GAME


