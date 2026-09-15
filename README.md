# ScenarioEngine 개발 작업공간

경찰청 소관 표준적합성시험의 공통 엔진, 표준별 시험 모듈, 에뮬레이터와
빌드에 필요한 공통 SDK를 하나의 Git 저장소에서 관리한다.

**목표: 다른 Windows PC에서도 이 저장소의 같은 브랜치를 체크아웃하고
동일한 소스와 SDK로 개발을 이어간다.**

## 포함 범위

- `scenarioengine`: WebSocket 제어와 시험 모듈 실행을 담당하는 공통 엔진.
- `scenarioenginewebsockmsg`: 공통 JSON 메시지 정의와 직렬화 코드.
- `*TestScenario`, `*TestMsg`, `iso14827testhelper`, `technicalregulation*`: 표준별 시험 구현.
- `GitsnDsrcEmulator`, `Itsk00126v1Emulator`, `ITSK00144_2Emulator`: 시험 상대 에뮬레이터.
- `dimz`, `codeconv`, `ASN.1.GITSN.LIB2`, `GitsnLicenseChkFree`: 정션을 실제 소스로 옮긴 공통 라이브러리.
- `ScenarioEngineSetup`: 기존 MSI 설치 프로젝트.
- `dependencies/artifacts`: 버전과 SHA-256이 고정된 OpenSSL 빌드 SDK. Git LFS로 관리.

30개 모듈의 목록과 원본 커밋/작업 파일 상태는 `dependencies.lock.json`에 기록했다.
원본 파일별 해시는 `doc/import-source-manifest.json`에 있다.
이번 범위에는 `fe`, `engine_x`, 별도 과제 원문 자료 폴더가 포함되지 않는다.
원본 모듈별 `.git`, 빌드 산출물, 실행 로그, 개인 설정과 인증키는 포함하지 않는다.

## 새 PC에서 시작

### 1. 도구 설치

- Windows x64
- Visual Studio 2022와 **Desktop development with C++** 워크로드
  (`.vsconfig`를 Visual Studio Installer에서 가져오기)
- Windows SDK 10.0 계열
- Git for Windows 및 Git LFS

```powershell
git lfs install
git clone https://github.com/GeonMyoung/ScenarioEngine.git C:\work\ScenarioEngine
Set-Location C:\work\ScenarioEngine
git switch main
git lfs pull
```

작업할 브랜치가 따로 있으면 `git switch`에서 해당 브랜치를 선택한다.
`C:\work\ScenarioEngine`은 예시이며 체크아웃 위치는 바꿔도 된다.

### 2. 의존성 설치 및 구조 확인

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\setup-sdk-dependencies.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\validate-workspace.ps1
```

설치 스크립트가 Git LFS로 받은 압축 파일의 크기와 SHA-256을 확인하고
`.deps\sdk`에 푼다. `Directory.Build.props`가 해당 체크아웃의 SDK를 선택하므로
사용자/시스템 환경 변수 설정이나 외부 `_SDK_` 폴더는 필요하지 않다.
구조 확인 성공 기준은 `FAIL=0`이다.

### 3. 엔진과 에뮬레이터 빌드

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\bootstrap-build.ps1 -Target All -Configuration Debug
```

| 선택값 | 빌드 대상 |
|---|---|
| `-Target Engine` | ScenarioEngine 실행 프로그램과 참조 라이브러리 |
| `-Target Emulators` | DSRC, ITSK-00126 v1, ITSK-00144-2 에뮬레이터 |
| `-Target All` | 엔진과 세 에뮬레이터 (기본값) |
| `-Target Tools` | TDC 및 JSON 코드 생성 도구 |

`-Configuration Release`로 Release 빌드, `-Rebuild`로 전체 재빌드를 수행한다.
빌드 로그는 `.local\build-logs`에 저장한다. 기본 검증 플랫폼은 **x64**다.
기존 Win32/구형 Visual Studio 프로젝트는 원본 소스로 보존하지만 이 SDK와
초기 구성의 검증 대상에는 포함하지 않는다.

### 4. Visual Studio에서 개발

- 솔루션: `scenarioengine\project\vs2022\ScenarioEngine.sln`
- 시작 프로젝트: `ScenarioEngineTest`
- 구성: `Debug | x64`
- 실행 파일: `scenarioengine\project\vs2022\DebugTest64\ScenarioEngineTest.exe`
- 디버그 실행 인수: `<시험 서버의 WebSocket URL> -debug`

빌드는 실행에 필요한 OpenSSL 및 pthread DLL을 출력 폴더에 복사한다.
실제 시험에는 제어 서버, 시험 구성, 대상 장비 또는 상대 에뮬레이터가 필요하다.
저장소를 체크아웃하는 것만으로 외부 서버와 시험 장비 환경까지 복원되지는 않는다.

## 생성 소스 관리

현재 개발 중인 생성 소스의 수정을 보존하기 위해 기본 빌드는 저장소의
`.c`, `.h`, `.tdo`를 그대로 사용하고 기존 CustomBuild 생성 명령을 실행하지 않는다.
`.tdc`/`.tjsonc`를 수정할 때는 먼저 `-Target Tools`로 `tdc.exe`, `tjsonc.exe`를
준비한다. 필요한 모듈만 `/p:ScenarioEngineRegenerateSources=true`를 지정해
빌드하고 생성된 diff를 확인한다. 전체 재생성을 기본 개발 절차로 사용하지 않는다.
ASN.1에서 생성된 C 코드도 저장소에 포함되어 있다.

## 설치 패키지

`ScenarioEngineSetup\ScenarioEngineSetup.vdproj`는 기존 Visual Studio Installer
Project다. MSI 편집/빌드에는 별도의 Microsoft Visual Studio Installer Projects
확장이 필요하다. CLI 기본 빌드는 MSI 프로젝트를 실행하지 않는다.
Release 엔진 빌드 후 `tools\prepare-installer.ps1`로 설치 프로젝트의 파일을 준비한다.
실제 MSI 생성과 설치 시험 결과는 별도로 확인한다.

## 초기 통합 기준과 확인 결과

[초기 통합 기록](doc/workspace-import.md)을 참고한다. 초기 통합의 목적은 소스·의존성의
재현 가능한 개발 환경 확보이며, 기존 시험 로직의 동작 수정은 별도 작업이다.
