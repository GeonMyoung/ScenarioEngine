# DATEX 간편 실행

## Scope and platform

Windows desktop companion for the existing DATEX manual bundle and web platform. This product context is local to `datexconformance/launcher`; it does not replace other ScenarioEngine interfaces.

## User and job

The current operator wants to verify individual DATEX detailed tests manually without repeatedly copying PowerShell commands, entering connection fields, choosing emulator modes, or managing processes. Existing single/subset/all selection and saved web reports must remain available.

## Established constraints

- Reuse the verified v9 engine and independent emulator; do not alter protocol verdicts or registered scenarios.
- Four adopted links, 14 configurations, 152 detailed items. Use official Korean system and test names.
- Web login stays in the browser. Do not collect or save the platform password.
- The operator obtains a new Agent connection URL from the web test page for each run.
- Preserve every run and all sent/received evidence. Clean up only processes created by this launcher.
- SUCCESS/FAIL and stop/error outcomes remain factual. No COMPLETE or post-evidence review workflow.

## Working UX choice

The user explicitly requires the real web workflow: launcher values must populate the existing Chrome form, its actual settings button must store/submit them, and the web start button must work. Do not send SETUP/START directly from the launcher. The user approved bundling a Chrome extension and separately approved installing it. Browser automation policy blocks the extension management URL; the user must perform that installation step. Inputs remain editable; the peer follows the configuration actually accepted by the engine.

## Evidence

The public deployed React controller bundles were inspected. The real settings click updates local form data and READY state before sending SETUP; direct WebSocket requests cannot update that UI. After the user installed the extension, v3 passed actual Chrome runs 250, 251 and 254: visible form values/settings summaries, direct web start, direct web edits, the WinForms event path, and saved reports. The launcher sent no direct SETUP/START. Preserve v2 report 243 as earlier sender verification, not proof of v3 web form automation.
