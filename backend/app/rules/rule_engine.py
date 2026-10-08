# TODO: Phase 4 — Contextual rule engine
#
# Inputs:
#   - detected_epcs:    list of EPCs read by YRM100 at exit time
#   - base_items:       always-required items (from MongoDB items collection)
#   - weather_context:  output from services/weather.py
#   - calendar_context: output from services/calendar.py
#
# Output:
#   - missing_items: list of required item names not present in detected_epcs
#
# Rule precedence:
#   1. Base required items (always checked)
#   2. Weather rules  (e.g. umbrella if raining)
#   3. Schedule rules (e.g. lab coat if lab day)
