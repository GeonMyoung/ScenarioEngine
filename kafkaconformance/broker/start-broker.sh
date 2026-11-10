#!/usr/bin/env bash
# Run in WSL. Uses only the dedicated G4 Kafka data directory and ports.
set -euo pipefail
g4_base=${G4_KAFKA_BASE:-/opt/gyeong4-kafka}
g4_home=${G4_KAFKA_HOME:-$g4_base/kafka_2.13-3.9.1}
g4_host=${G4_KAFKA_HOST:-$(hostname -I | awk '{print $1}')}
g4_source=$(cd -- "$(dirname -- "$0")" && pwd)
test -x "$g4_home/bin/kafka-server-start.sh" || { echo 'Prepare Apache Kafka 3.9.1 and Java 17 first.' >&2; exit 1; }
if ss -ltnH '( sport = :29092 or sport = :29093 )' | grep -q .; then
    echo '29092/29093 is occupied; existing processes are not changed.' >&2; exit 1
fi
mkdir -p "$g4_base"
sed "s@advertised.listeners=PLAINTEXT://127.0.0.1:29092@advertised.listeners=PLAINTEXT://$g4_host:29092@;s@log.dirs=/opt/gyeong4-kafka/data@log.dirs=$g4_base/data@" "$g4_source/server.properties" > "$g4_base/server.properties"
if [ ! -f "$g4_base/data/meta.properties" ]; then
    "$g4_home/bin/kafka-storage.sh" format -t G4KafkaDev20260925abcdeQ -c "$g4_base/server.properties"
fi
echo "Dedicated test broker: $g4_host:29092 (PLAINTEXT)."
exec "$g4_home/bin/kafka-server-start.sh" "$g4_base/server.properties"
