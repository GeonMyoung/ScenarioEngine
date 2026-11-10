# DATEX launcher design

Mode: Operate. Extend the existing manual's restrained dark green / warm neutral identity with familiar Windows controls. No new visual brand, marketing content, decorative graphics, or animation.

- Malgun Gothic, readable fixed scale, native focus and keyboard affordances.
- Left: environment inputs and detailed-test selection tabs. Right: new web connection, explicit environment apply, applied-value summary, separate start action, progress and result actions.
- Applying configuration does not start the peer or the test. Editing inputs or selected items invalidates readiness. Initial values remain visible and editable; reset defaults and find-free-port actions only change inputs.
- In v3, apply populates the existing Chrome form and invokes its actual settings button. The web's settings summary and start-enabled state are authoritative. Starting from the web directly must prepare the peer and update the desktop run view. No direct SETUP/START bypass.
- Default is one detailed test. Single/subset/all remain explicit.
- Show the next required user action in Korean. Hide commands, case keys, process IDs and paths from the primary flow.
- Distinguish preparing, running, saving report, completed, failed and stopped. Disable conflicting controls while busy.
- Web password is never an input. Connection URL is used only for the specified platform.
- Result review by the human is a separate explicit action from the automatic verdict.
- Support resizing and DPI scaling; the detailed list and log area scroll instead of clipping.
