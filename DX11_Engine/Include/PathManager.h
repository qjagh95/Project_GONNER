#pragma once
JEONG_BEGIN

class JEONG_DLL PathManager
{
public:
	bool Init();
	bool AddPath(const string& KeyName, const wstring& PathName, const string& BaseKeyName = ROOT_PATH);
	const TCHAR* FindPath(const string& KeyName);
	const string FindPathMultiByte(const string& KeyName);

private:
	unordered_map<string, wstring> PathMap;
	string m_MultiBytePath;

public:
	CLASS_IN_SINGLE(PathManager)
};

JEONG_END

