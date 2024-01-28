@echo off
cd /d %~dp0
cd ../
@echo on

cloc --exclude-dir=build,PulsarionWindowing/vendor,PulsarionMedia/vendor/,PulsarionCore/vendor,PulsarionMath/vendor  --by-file --csv --quiet --report-file=build/line_count.csv /