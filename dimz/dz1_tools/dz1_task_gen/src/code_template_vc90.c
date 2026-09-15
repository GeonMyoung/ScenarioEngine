#include "code_template.h"

#define VC90_PROJ_HEAD(sym_name, sym_guid_literal) \
Dz1T("<?xml version=\"1.0\" encoding=\"ks_c_5601-1987\"?>"),\
Dz1T("<VisualStudioProject"),\
Dz1T("	ProjectType=\"Visual C++\""),\
Dz1T("	Version=\"9.00\""),\
Dz1T("	Name=\"[[") #sym_name Dz1T("]]\""),\
Dz1T("	ProjectGUID=\"[[") #sym_guid_literal Dz1T("]]\""),\
Dz1T("	RootNamespace=\"[[") #sym_name Dz1T("]]\""),\
Dz1T("	Keyword=\"Win32Proj\""),\
Dz1T("	TargetFrameworkVersion=\"196613\">"),\
Dz1T("	<Platforms>"),\
Dz1T("		<Platform Name=\"Win32\"/>"),\
Dz1T("	</Platforms>"),\
Dz1T("	<ToolFiles>"),\
Dz1T("	</ToolFiles>")

#define MSVC_STR_PROJ_CONF_CONSOLE				"1"
#define MSVC_STR_PROJ_CONF_STATIC_LIB			"4"

#define MSVC_STR_PROJ_MFC_USE_LIB				"1"
#define MSVC_STR_PROJ_MFC_USE_DLL				"2"

#define MSVC_STR_PROJ_CHARSET_MBCS				"2"

#define VC90_PROJ_CONF_HEAD(str_config_name, string_path_prefix, str_conf_type, str_useof_mfc, str_charset) \
Dz1T("		<Configuration"),\
Dz1T("			Name=\"") #str_config_name Dz1T("|Win32\""),\
Dz1T("			OutputDirectory=\"") string_path_prefix Dz1T("$(ConfigurationName)\\\""),\
Dz1T("			IntermediateDirectory=\"") string_path_prefix Dz1T("$(ConfigurationName)\\\""),\
Dz1T("			ConfigurationType=\"") Dz1T(str_conf_type) Dz1T("\""),\
Dz1T("			UseOfMFC=\"") Dz1T(str_useof_mfc) Dz1T("\""),\
Dz1T("			CharacterSet=\"") Dz1T(str_charset) Dz1T("\">")

#define MSVC_STR_DEFINE_LIB						"_LIB"
#define MSVC_STR_DEFINE_CONSOLE					"_CONSOLE"

#define MSVC_STR_DEFINE_BUILD_DEBUG				"_DEBUG"
#define MSVC_STR_DEFINE_BUILD_RELEASE			"NDEBUG"

#define MSVC_STR_DBG_INFO_NONE					"0"
#define MSVC_STR_DBG_INFO_C7					"1"

#define MSVC_STR_OPTIMIZE_NONE					"0"
#define MSVC_STR_OPTIMIZE_SPEED					"2"

#define MSVC_STR_INLINE_EXPAND_DEFAULT			"0"
#define MSVC_STR_INLINE_EXPAND_INLINEONLY		"1"

#define MSVC_STR_RUNTIME_CHK_DEFAULT			"0"
#define MSVC_STR_RUNTIME_CHK_ALL				"3"

#define MSVC_STR_RUNTIME_LIB_MT					"0"
#define MSVC_STR_RUNTIME_LIB_MD					"1"
#define MSVC_STR_RUNTIME_LIB_MTd				"2"
#define MSVC_STR_RUNTIME_LIB_MDd				"3"
// -------------------------------------------------------------------------------------------------------
// C/C++
#define VC90_PROJ_CONF_TOOL_COMPILER(str_define_type, str_define_build, str_dbg_info, str_optimize, str_inline_expand, str_runtime_chk, str_runtime_lib) \
Dz1T("			<Tool"),\
Dz1T("				Name=\"VCCLCompilerTool\""),\
Dz1T("				AdditionalIncludeDirectories=\"[[PROJ_INCLUDES]];[[PTHREAD_ROOT]]\""),\
Dz1T("				DebugInformationFormat=\"") Dz1T(str_dbg_info) Dz1T("\""),\
Dz1T("				WarningLevel=\"3\""),\
Dz1T("				Optimization=\"") Dz1T(str_optimize) Dz1T("\""),\
Dz1T("				InlineFunctionExpansion=\"") Dz1T(str_inline_expand) Dz1T("\""),\
Dz1T("				PreprocessorDefinitions=\"WIN32;") Dz1T(str_define_type) Dz1T(";__CLEANUP_C;[[SYSTEM_ENDIAN_DEF]];__WORDSIZE=32;") Dz1T(str_define_build) Dz1T("\""),\
Dz1T("				StringPooling=\"true\""),\
Dz1T("				MinimalRebuild=\"false\""),\
Dz1T("				BasicRuntimeChecks=\"") Dz1T(str_runtime_chk) Dz1T("\""),\
Dz1T("				RuntimeLibrary=\"") Dz1T(str_runtime_lib) Dz1T("\""),\
Dz1T("				EnableFunctionLevelLinking=\"false\""),\
Dz1T("				UsePrecompiledHeader=\"0\""),\
Dz1T("				PrecompiledHeaderFile=\"$(IntDir)$(TargetName).pch\""),\
Dz1T("				AssemblerListingLocation=\"$(IntDir)\""),\
Dz1T("				ObjectFile=\"$(IntDir)\""),\
Dz1T("				ProgramDataBaseFileName=\"$(IntDir)$(TargetName).pdb\""),\
Dz1T("				XMLDocumentationFileName=\"$(IntDir)$(TargetName).xml\""),\
Dz1T("				CompileAs=\"0\""),\
Dz1T("			/>")

// -------------------------------------------------------------------------------------------------------
// 라이브러리 관리자
#define VC90_PROJ_CONF_TOOL_AR \
Dz1T("			<Tool"),\
Dz1T("				Name=\"VCLibrarianTool\""),\
Dz1T("				OutputFile=\"$(OutDir)$(ProjectName).lib\""),\
Dz1T("			/>")

// -------------------------------------------------------------------------------------------------------
// 링커
#define VC90_PROJ_CONF_TOOL_LINK \
Dz1T("			<Tool"),\
Dz1T("				Name=\"VCLinkerTool\""),\
Dz1T("				OutputFile=\"$(OutDir)$(ProjectName).exe\""),\
Dz1T("				LinkIncremental=\"0\""),\
Dz1T("				AdditionalLibraryDirectories=\"\""),\
Dz1T("				AdditionalDependencies=\"\""),\
Dz1T("				DelayLoadDLLs=\"$(NOINHERIT)\""),\
Dz1T("				GenerateDebugInformation=\"true\""),\
Dz1T("				SubSystem=\"1\""),\
Dz1T("				TargetMachine=\"1\""),\
Dz1T("			/>")

// -------------------------------------------------------------------------------------------------------
// 찾아보기 정보
#define VC90_PROJ_CONF_TOOL_BSC \
Dz1T("			<Tool"),\
Dz1T("				Name=\"VCBscMakeTool\""),\
Dz1T("				OutputFile=\"$(OutDir)$(TargetName).bsc\""),\
Dz1T("			/>")

// -------------------------------------------------------------------------------------------------------
// 빌드 이벤트
#define VC90_PROJ_CONF_TOOL_BEVENT \
Dz1T("			<Tool"),\
Dz1T("				Name=\"VCPostBuildEventTool\""),\
Dz1T("					CommandLine=\"copy [[PTHREAD_ROOT]]\\project\\vc90\\$(ConfigurationName)\\pthreadVC2.dll $(IntDir)\""),\
Dz1T("			/>")

#define VC90_PROJ_CONF_MID \
Dz1T("	<References>"),\
Dz1T("	</References>")

#define VC90_PROJ_CONF_TAIL \
Dz1T("		</Configuration>")

#define VC90_PROJ_TAIL \
Dz1T("	<Globals>"),\
Dz1T("	</Globals>"),\
Dz1T("</VisualStudioProject>")

#define VC90_PROJ_LIB_CONF_ALL \
Dz1T("	<Configurations>"),\
VC90_PROJ_CONF_HEAD(Debug, Dz1T(""), MSVC_STR_PROJ_CONF_STATIC_LIB, MSVC_STR_PROJ_MFC_USE_LIB, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_LIB, MSVC_STR_DEFINE_BUILD_DEBUG, MSVC_STR_DBG_INFO_C7, MSVC_STR_OPTIMIZE_NONE, MSVC_STR_INLINE_EXPAND_DEFAULT, MSVC_STR_RUNTIME_CHK_ALL, MSVC_STR_RUNTIME_LIB_MTd),\
VC90_PROJ_CONF_TOOL_AR,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(DebugDLL, Dz1T(""), MSVC_STR_PROJ_CONF_STATIC_LIB, MSVC_STR_PROJ_MFC_USE_DLL, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_LIB, MSVC_STR_DEFINE_BUILD_DEBUG, MSVC_STR_DBG_INFO_C7, MSVC_STR_OPTIMIZE_NONE, MSVC_STR_INLINE_EXPAND_DEFAULT, MSVC_STR_RUNTIME_CHK_ALL, MSVC_STR_RUNTIME_LIB_MDd),\
VC90_PROJ_CONF_TOOL_AR,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(Release, Dz1T(""), MSVC_STR_PROJ_CONF_STATIC_LIB, MSVC_STR_PROJ_MFC_USE_LIB, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_LIB, MSVC_STR_DEFINE_BUILD_RELEASE, MSVC_STR_DBG_INFO_NONE, MSVC_STR_OPTIMIZE_SPEED, MSVC_STR_INLINE_EXPAND_INLINEONLY, MSVC_STR_RUNTIME_CHK_DEFAULT, MSVC_STR_RUNTIME_LIB_MT),\
VC90_PROJ_CONF_TOOL_AR,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(ReleaseDLL, Dz1T(""), MSVC_STR_PROJ_CONF_STATIC_LIB, MSVC_STR_PROJ_MFC_USE_DLL, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_LIB, MSVC_STR_DEFINE_BUILD_RELEASE, MSVC_STR_DBG_INFO_NONE, MSVC_STR_OPTIMIZE_SPEED, MSVC_STR_INLINE_EXPAND_INLINEONLY, MSVC_STR_RUNTIME_CHK_DEFAULT, MSVC_STR_RUNTIME_LIB_MD),\
VC90_PROJ_CONF_TOOL_AR,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TAIL,\
Dz1T("	</Configurations>")

#define VC90_PROJ_FILE_HDR_TDC_CONF(str_config_name) \
Dz1T("					<FileConfiguration"),\
Dz1T("						Name=\"") #str_config_name Dz1T("|Win32\">"),\
Dz1T("						<Tool"),\
Dz1T("							Name=\"VCCustomBuildTool\""),\
Dz1T("							CommandLine=\"[[DIMZ_TOOLS_PATH]]\\tdc.exe -I [[PROJ_INCLUDES]] -s ..\\..\\src $(InputName).tdc\""),\
Dz1T("							Outputs=\"..\\..\\src\\$(InputName).c;..\\..\\include\\$(InputName).h;..\\..\\include\\$(InputName).tdo\"/>"),\
Dz1T("					</FileConfiguration>")

#define VC90_PROJ_FILE_HDR_TDC_CONF_ALL \
VC90_PROJ_FILE_HDR_TDC_CONF(Debug),\
VC90_PROJ_FILE_HDR_TDC_CONF(DebugDLL),\
VC90_PROJ_FILE_HDR_TDC_CONF(Release),\
VC90_PROJ_FILE_HDR_TDC_CONF(ReleaseDLL)

#define VC90_PROJ_FILE_SRC_TDC_CONF(str_config_name) \
Dz1T("					<FileConfiguration"),\
Dz1T("						Name=\"") #str_config_name Dz1T("|Win32\">"),\
Dz1T("						<Tool"),\
Dz1T("							Name=\"VCCustomBuildTool\""),\
Dz1T("							CommandLine=\"[[DIMZ_TOOLS_PATH]]\\tdc.exe -I ..\\..\\src;[[PROJ_INCLUDES]] $(InputName).tdc\""),\
Dz1T("							Outputs=\"..\\..\\src\\$(InputName).c;..\\..\\src\\$(InputName).h;..\\..\\src\\$(InputName).tdo\"/>"),\
Dz1T("					</FileConfiguration>")

#define VC90_PROJ_FILE_SRC_TDC_CONF_ALL \
VC90_PROJ_FILE_SRC_TDC_CONF(Debug),\
VC90_PROJ_FILE_SRC_TDC_CONF(DebugDLL),\
VC90_PROJ_FILE_SRC_TDC_CONF(Release),\
VC90_PROJ_FILE_SRC_TDC_CONF(ReleaseDLL)

Dz1Str vc90_library_proj[] = {
VC90_PROJ_HEAD(PROJ_NAME, PROJ_TARGET_GUID),
VC90_PROJ_LIB_CONF_ALL,
VC90_PROJ_CONF_MID,
Dz1T("	<Files>"),
Dz1T("		<Filter"),
Dz1T("		<Filter"),
Dz1T("			Name=\"리소스 파일\""),
Dz1T("			Filter=\"rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("		</Filter>"),
Dz1T("			Name=\"소스 파일\""),
Dz1T("			Filter=\"cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TDC_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("		</Filter>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"헤더 파일\""),
Dz1T("			Filter=\"h;hpp;hxx;hm;inl;inc;xsd\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\include\\[[PROJ_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\include\\[[PROJ_TDC_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\\\include[[PROJ_TDC_NAME]].tdc\">"),
						VC90_PROJ_FILE_HDR_TDC_CONF_ALL,
Dz1T("				</File>"),
Dz1T("		</Filter>"),
Dz1T("		<File"),
Dz1T("			RelativePath=\"..\\..\\ReadMe.txt\">"),
Dz1T("		</File>"),
Dz1T("	</Files>"),
VC90_PROJ_TAIL,
NULL
};

Dz1Str vc90_task_proj[] = {
VC90_PROJ_HEAD(PROJ_NAME, PROJ_TARGET_GUID),
VC90_PROJ_LIB_CONF_ALL,
VC90_PROJ_CONF_MID,
Dz1T("	<Files>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"리소스 파일\""),
Dz1T("			Filter=\"rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("		</Filter>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"소스 파일\""),
Dz1T("			Filter=\"cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("			<Filter"),
Dz1T("				Name=\"engine\""),
Dz1T("				Filter=\"cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx\">"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ARG_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ARG_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ARG_NAME]].tdc\">"),
						VC90_PROJ_FILE_SRC_TDC_CONF_ALL
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ENV_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ENV_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_ENV_NAME]].tdc\">"),
						VC90_PROJ_FILE_SRC_TDC_CONF_ALL
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TMR_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TMR_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TMR_NAME]].tdc\">"),
						VC90_PROJ_FILE_SRC_TDC_CONF_ALL
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_TMR_UTIL_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("			</Filter>"),
Dz1T("			<Filter"),
Dz1T("				Name=\"message\""),
Dz1T("				Filter=\"cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx\">"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_MSG_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_MSGS_NAME]].h\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_MSGS_NAME]].c\">"),
Dz1T("				</File>"),
Dz1T("				<File"),
Dz1T("					RelativePath=\"..\\..\\src\\[[PROJ_MSGS_NAME]].tdc\">"),
						VC90_PROJ_FILE_SRC_TDC_CONF_ALL
Dz1T("				</File>"),
Dz1T("			</Filter>"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\src\\[[PROJ_NAME]].c\">"),
Dz1T("			</File>"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\src\\[[PROJ_TDC_NAME]].c\">"),
Dz1T("			</File>"),
Dz1T("		</Filter>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"헤더 파일\""),
Dz1T("			Filter=\"h;hpp;hxx;hm;inl;inc;xsd\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\include\\[[PROJ_NAME]].h\">"),
Dz1T("			</File>"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\include\\[[PROJ_TDC_NAME]].h\">"),
Dz1T("			</File>"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\\\include\\[[PROJ_TDC_NAME]].tdc\">"),
					VC90_PROJ_FILE_HDR_TDC_CONF_ALL,
Dz1T("			</File>"),
Dz1T("		</Filter>"),
Dz1T("		<File"),
Dz1T("			RelativePath=\"..\\..\\ReadMe.txt\">"),
Dz1T("		</File>"),
Dz1T("	</Files>"),
VC90_PROJ_TAIL,
NULL
};

#define VC90_PROJ_CONSOLE_CONF_ALL \
Dz1T("	<Configurations>"),\
VC90_PROJ_CONF_HEAD(Debug, Dz1T("Test"), MSVC_STR_PROJ_CONF_CONSOLE, MSVC_STR_PROJ_MFC_USE_LIB, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_CONSOLE, MSVC_STR_DEFINE_BUILD_DEBUG, MSVC_STR_DBG_INFO_C7, MSVC_STR_OPTIMIZE_NONE, MSVC_STR_INLINE_EXPAND_DEFAULT, MSVC_STR_RUNTIME_CHK_ALL, MSVC_STR_RUNTIME_LIB_MTd),\
VC90_PROJ_CONF_TOOL_LINK,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TOOL_BEVENT,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(DebugDLL, Dz1T("Test"), MSVC_STR_PROJ_CONF_CONSOLE, MSVC_STR_PROJ_MFC_USE_DLL, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_CONSOLE, MSVC_STR_DEFINE_BUILD_DEBUG, MSVC_STR_DBG_INFO_C7, MSVC_STR_OPTIMIZE_NONE, MSVC_STR_INLINE_EXPAND_DEFAULT, MSVC_STR_RUNTIME_CHK_ALL, MSVC_STR_RUNTIME_LIB_MDd),\
VC90_PROJ_CONF_TOOL_LINK,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TOOL_BEVENT,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(Release, Dz1T("Test"), MSVC_STR_PROJ_CONF_CONSOLE, MSVC_STR_PROJ_MFC_USE_LIB, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_CONSOLE, MSVC_STR_DEFINE_BUILD_RELEASE, MSVC_STR_DBG_INFO_NONE, MSVC_STR_OPTIMIZE_SPEED, MSVC_STR_INLINE_EXPAND_INLINEONLY, MSVC_STR_RUNTIME_CHK_DEFAULT, MSVC_STR_RUNTIME_LIB_MT),\
VC90_PROJ_CONF_TOOL_LINK,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TOOL_BEVENT,\
VC90_PROJ_CONF_TAIL,\
VC90_PROJ_CONF_HEAD(ReleaseDLL, Dz1T("Test"), MSVC_STR_PROJ_CONF_CONSOLE, MSVC_STR_PROJ_MFC_USE_DLL, MSVC_STR_PROJ_CHARSET_MBCS),\
VC90_PROJ_CONF_TOOL_COMPILER(MSVC_STR_DEFINE_CONSOLE, MSVC_STR_DEFINE_BUILD_RELEASE, MSVC_STR_DBG_INFO_NONE, MSVC_STR_OPTIMIZE_SPEED, MSVC_STR_INLINE_EXPAND_INLINEONLY, MSVC_STR_RUNTIME_CHK_DEFAULT, MSVC_STR_RUNTIME_LIB_MD),\
VC90_PROJ_CONF_TOOL_LINK,\
VC90_PROJ_CONF_TOOL_BSC,\
VC90_PROJ_CONF_TOOL_BEVENT,\
VC90_PROJ_CONF_TAIL,\
Dz1T("	</Configurations>")


Dz1Str vc90_test_proj[] = {
VC90_PROJ_HEAD(PROJ_TEST_NAME, PROJ_TEST_GUID),
VC90_PROJ_CONSOLE_CONF_ALL,
VC90_PROJ_CONF_MID,
Dz1T("	<Files>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"리소스 파일\""),
Dz1T("			Filter=\"rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("		</Filter>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"소스 파일\""),
Dz1T("			Filter=\"cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("			<File"),
Dz1T("				RelativePath=\"..\\..\\[[PROJ_TEST_NAME]].c\">"),
Dz1T("			</File>"),
Dz1T("		</Filter>"),
Dz1T("		<Filter"),
Dz1T("			Name=\"헤더 파일\""),
Dz1T("			Filter=\"h;hpp;hxx;hm;inl;inc;xsd\""),
Dz1T("			UniqueIdentifier=\"[[$GUID]]\">"),
Dz1T("		</Filter>"),
Dz1T("		<File"),
Dz1T("			RelativePath=\"..\\..\\ReadMe.txt\">"),
Dz1T("		</File>"),
Dz1T("	</Files>"),
VC90_PROJ_TAIL,
NULL
};

