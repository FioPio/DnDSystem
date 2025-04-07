dnd-platform/
│── cmd/                 # Entrypoints de l'aplicació (CLI, API, etc.)
│   ├── api/             # Servei HTTP per interactuar amb la plataforma
│   ├── cli/             # Possible interfície de línia de comandes
│── internal/            # Lògica interna (no exposada com a API pública)
│   ├── combat/          # Mòdul per gestionar el combat
│   │   ├── actions/     # Accions disponibles en combat (atacar, defensar, moure, etc.)
│   │   ├── initiative/  # Sistema d'iniciativa
│   │   ├── turns/       # Gestió de torns i ordre d'iniciativa
│   │   ├── conditions/  # Condicions com encanteris, efectes, etc.
│   │   ├── combat.go    # Coordinació general del combat
│   ├── entities/        # Models de personatges, criatures i NPCs
│   ├── game/            # Gestió de partides i sessions
│   ├── rules/           # Implementació de les regles del joc
│   ├── dice/            # Subsistema per gestionar tirades de daus
│── pkg/                 # Llibreries reutilitzables
│   ├── utils/           # Funcions auxiliars (random, logs, etc.)
│   ├── storage/         # Persistència (SQLite, JSON, PostgreSQL, etc.)
│── web/                 # Possible interfície web
│── testdata/            # Fitxers per a tests
│── go.mod               # Fitxer de dependències
│── README.md            # Documentació del projecte
