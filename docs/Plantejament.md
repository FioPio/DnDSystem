Explicació de la modularitat

    Modularitat i Escalabilitat

        Separo el combat de la gestió del joc per fer-lo independent i reutilitzable.

        rules/ permetria suportar diferents edicions de DnD o inclús jocs personalitzats.

    Generalització de Personatges i Criatures

        A entities/, cada entitat (jugadors, NPCs, monstres) compartiria una interfície comuna, amb atributs generals com punts de vida, classe d'armadura i velocitat.

    Sistema de Combat Flexible

        El combat no depèn d'un tipus concret de partida, sinó que s'organitza en accions, iniciatives i torns.

    Persistència i Extensibilitat

        storage/ podria tenir adaptadors per a diferents bases de dades o guardar l'estat en memòria.

    Facilitat per a Futurs Desenvolupaments

        Si vull afegir narrativa i rol, puc fer-ho a game/ sense modificar el combat.

        Si vull afegir una UI, web/ o cli/ ho permetrien sense tocar el core de la lògica.

Amb aquesta estructura, el projecte seria modular i fàcil d'expandir. Et sembla bé aquest enfocament o hi ha alguna part que voldries canviar?
Heu dit:
Com modelaries Actions, BonusActions i Reactions?
ChatGPT ha dit:

Per modelar Actions, BonusActions i Reactions en un sistema de combat flexible de DnD, crearia una interfície comuna que representi qualsevol tipus d'acció, i després implementaria cada tipus d'acció com a estructures separades.
🎯 1. Interfície comuna per a accions

Com que totes les accions tenen elements en comú (com qui les fa, quan es poden fer, i què fan), definiria una interfície genèrica:

package actions

import "dnd-platform/internal/entities"

// ActionType defineix el tipus d'acció
type ActionType string

const (
    Action      ActionType = "Action"
    BonusAction ActionType = "BonusAction"
    Reaction    ActionType = "Reaction"
)

// Action és la interfície que totes les accions han d'implementar
type Action interface {
    GetName() string              // Nom de l'acció (ex: "Atac", "Llançar Encantament")
    GetType() ActionType          // Retorna si és una Acció, BonusAction o Reaction
    CanUse(user *entities.Actor) bool // Retorna si l'usuari pot fer aquesta acció
    Execute(user *entities.Actor, target *entities.Actor) string // Aplica l'acció
}

Aquesta interfície permet que qualsevol acció (sigui una acció normal, una acció bonus o una reacció) es tracti de manera genèrica al sistema de combat.
⚔️ 2. Implementació d'algunes accions concretes

Aquí hi ha alguns exemples d’accions basades en la interfície:
Acció d'Atac Normal

package actions

import "dnd-platform/internal/entities"

type Attack struct {
    Name   string
    Damage int
}

func (a *Attack) GetName() string {
    return a.Name
}

func (a *Attack) GetType() ActionType {
    return Action
}

func (a *Attack) CanUse(user *entities.Actor) bool {
    return user.ActionPoints > 0 // Exemple de limitació (ha de tenir punts d'acció disponibles)
}

func (a *Attack) Execute(user *entities.Actor, target *entities.Actor) string {
    if !a.CanUse(user) {
        return user.Name + " no pot atacar ara!"
    }
    target.HP -= a.Damage
    user.ActionPoints-- // Restem un punt d'acció després d'atacar
    return user.Name + " ataca " + target.Name + " i fa " + fmt.Sprint(a.Damage) + " punts de dany!"
}

BonusAction: "Acció d'Inspiració del Bard"

package actions

import "dnd-platform/internal/entities"

type BardicInspiration struct {
    BonusAmount int
}

func (b *BardicInspiration) GetName() string {
    return "Bardic Inspiration"
}

func (b *BardicInspiration) GetType() ActionType {
    return BonusAction
}

func (b *BardicInspiration) CanUse(user *entities.Actor) bool {
    return user.BonusActionPoints > 0
}

func (b *BardicInspiration) Execute(user *entities.Actor, target *entities.Actor) string {
    if !b.CanUse(user) {
        return user.Name + " no pot donar inspiració ara!"
    }
    target.BonusDice += b.BonusAmount
    user.BonusActionPoints--
    return user.Name + " inspira " + target.Name + ", donant-li un + " + fmt.Sprint(b.BonusAmount) + " a la seva pròxima tirada!"
}

Reaction: "Atac d'Oportunitat"

package actions

import "dnd-platform/internal/entities"

type OpportunityAttack struct {
    Damage int
}

func (o *OpportunityAttack) GetName() string {
    return "Opportunity Attack"
}

func (o *OpportunityAttack) GetType() ActionType {
    return Reaction
}

func (o *OpportunityAttack) CanUse(user *entities.Actor) bool {
    return user.ReactionPoints > 0
}

func (o *OpportunityAttack) Execute(user *entities.Actor, target *entities.Actor) string {
    if !o.CanUse(user) {
        return user.Name + " no pot reaccionar ara!"
    }
    target.HP -= o.Damage
    user.ReactionPoints--
    return user.Name + " fa un atac d'oportunitat contra " + target.Name + " i fa " + fmt.Sprint(o.Damage) + " de dany!"
}

🔄 3. Com s'usarien aquestes accions en el combat

Cada jugador o criatura tindria una llista d'accions disponibles:

package entities

import "dnd-platform/internal/actions"

type Actor struct {
    Name              string
    HP                int
    ActionPoints      int
    BonusActionPoints int
    ReactionPoints    int
    BonusDice         int
    AvailableActions  []actions.Action
}

Quan un jugador vol fer una acció en el seu torn, el sistema cridaria:

func TakeAction(user *Actor, action actions.Action, target *Actor) string {
    return action.Execute(user, target)
}

📌 Avantatges d'aquest sistema

✅ Extensible – Es poden afegir fàcilment més accions com encanteris, habilitats especials, etc.
✅ Generalitzat – El combat no depèn d'una acció específica, sinó que tracta totes les accions com a objectes amb un comportament comú.
✅ Fàcil d'integrar – Permet que cada classe de personatge o criatura tingui accions personalitzades.

Amb aquest sistema modular, afegir nous tipus d'accions o noves mecàniques serà fàcil en el futur. Et sembla un bon plantejament? 😊