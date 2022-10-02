# LINGO
- IFC
Intelligence-Focus Calculations. They will both be used as a scalar; with Focus having the most weight.
# Lua
## 
## Networking API
Lua will interact with C to create sockets. This is a core step to implementing multiplayer.
# Better NPC AI
## NPC Personalities & Beliefs
For both of these, I will be using a range of personality and belief ranges, as the below will show:
### RAW DUMP
        "spirituality"      : ({"Athiest":1, "Spiritual":4, "Religious Fanatic":7}),  # 7 tiers, from Athiest to Spiritual to Religious Fanatic
        "politics"          : ({"Libertarian":1, "Moderate":4, "Authoritarian":7}),  # 7 tiers, from Free to Moderate to Authoritarian
        "order"             : ({"Ungovernable":1, "Balanced":7, "Strict":7}),  # 7 tiers, from Ungovernable to Strict
        "trends"            : ({"Apathetic":1, "Balanced":3, "Trendsetter":5}),  # 5 tiers, from Apathetic to Trendsetter
        "loyalty"           : ({"Unloyal":1, "Noble":3, "Devout Follower":5}),  # 5 tiers, from Unloyal to Noble to Devout Follower
        "family"            : ({"Outcast":1, "Balanced":3, "Family Dependent":5}),  # 5 tiers, from Outcast to Family Person
        "friendship"        : ({"Unassociative":1, "Balanced":3, "Strong Attachment":5}),  # 5 tiers, from Unassociative to Strong Attachment
        "power"             : ({"Submissive":1, "Narcissist":3, "Megalomaniac":5}),  # 5 tiers, from Submissive to X Narcissist to Megalomaniac
        "wealth"            : ({"Hates Wealth":1, "Neutral":4, "Loves Wealth":7}),  # 7 tiers, from Hates Wealth to Neutral to Loves Wealth
        "materialism"       : ({"Nonmaterialistic":1, "Neutral":3, "Materialistic":5}),  # 5 tiers, from Nonmaterialistic to Neutral to Materialistic
        "commerce"          : ({"Socialistic":1, "Balanced":3, "Capitalistic":5}),  # 5 tiers, from Socialistic to Capitalistic
        "fairness"          : ({"Arrogant":1, "Balanced":3, "Strict Egalitarian":5}),  # 5 tiers, from Arrogant to Strict Egalitarian
        "art"               : ({"Unappreciative":1, "Balanced":3, "Art Lover":5}),  # 5 tiers, from Unappreciative to Art Lover
        "tranquility"       : ({"Tumultuous":1, "Balanced":3, "Harmonious":5}),  # 5 tiers, from Tumultuous to Harmonious
        "evaluation"        : ({"Generous":1, "Scrutinous":3, "Perfectionist":5}),  # 5 tiers, from Generous to Scrutinous to Perfectionist
        "skill"             : ({"Unappreciative":1, "Balanced":3, "Appreciative":5}),  # 5 tiers, from Unappreciative to Appreciative
        "labor"             : ({"Lazy":1, "Balanced":3, "Workaholic":5}),  # 5 tiers, from Lazy to
        "sacrifice"         : ({"Repudiative":1, "Sacrificial":3, "Willfully Transient":5}),  # 5 tiers, from X to Sacrificial
        "hedonism"          : ({"Ascetic":1, "Balanced":3, "Carnal":5}),  # 5 tiers, from Ascetic to Carnal
        "humor"             : ({"Lame":1, "Balanced":3, "Antic":5}),  # 5 tiers, from Lame to Antic
        "respect"           : ({"Disrespectful":1, "Balanced":3, "Respectful":5}),  # 5 tiers, from Disrespectful to Respectful
        "competition"       : ({"Lackadaisical":1, "Balanced":3, "Rivalrous":5}),  # 5 tiers, from Lackadaisical to Rivalrous
        "individualism"     : ({"Collectivist":1, "Balanced":3, "Egoist":5}),  # 5 tiers, from Collectivist to Egoist
        "perserverance"     : ({"Uncommittive":1, "Determined":3, "Resilient":5}),  # 5 tiers, from X to Resilient
        "leisure"           : ({"Lazy":1, "Moderate":3, "Busybody":5}),  # 5 tiers, from Lazy to Busybody
        "nature"            : ({"Biophobic":1, "Balanced":3, "Ecophilic":5}),  # 5 tiers, from Biophobic to Ecophilic
        "peace"             : ({"Warmonger":1, "Balanced":3, "Pacifist":5}),  # 5 tiers, from Warmonger to Pacifist
        "independence"      : ({"Dependent":1, "Balanced":3, "Independent":5}),  # 5 tiers, from Dependent to Independent
        "rationality"       : ({"Irrational":1, "Rational":3, "Acquiscing":5}),  # 5 tiers, from Irrational to Sensible  to Acquiscing
        "conscientiousness" : ({"Oblivious":1, "Conscious":3, "Self Aware":5}),  # 5 tiers, from Oblivious to Self Aware
        "love"              : ({"Unloving":1, "Loving":3, "Obsessive":5}),  # 5 tiers, from Unloving to Obsessive
        "hate"              : ({"Unhating":1, "Disdainful":3, "Hateful":5}),  # 5 tiers, from Unhating to Disdainful
        "technology"        : ({"Luddite":1, "Balanced":3, "Technomaniac":5}),  # 5 tiers, from Luddite to Technomaniac
        "socialness"        : ({"Antisocial":1, "Balanced":3, "Social Butterfly":5}),  # 5 tiers, from Antisocial to Social Butterfly
        "tradition"         : ({"Progressive":1, "Balanced":3, "Traditionalist":5}),  # 5 tiers, from Progressive to Traditionalist
        "knowledge"         : ({"Ignorant":1, "Normal":3, "Open Minded":5}),  # 5 tiers, from Ignorant to Normal to Open Minded
        "honesty"           : ({"Compulsive Liar":1, "Balanced":3, "Honest":5}),  # 5 tiers, from Compulsive Liar to Balanced to Honest

        "curiosity": (preset={"Noncurious":1, "Curious":4, "Inquisitive":7}),  # 7 tiers, from Noncurious to Curious to Inquisitive
        "imagination": ({"Unimaginative":1, "Intermediate":4, "Flights of Fancies":7}),  # 7 tiers, from Unimaginative to Intermediate to Flights of Fancies
        "confidence": ({"Fearful":1, "Brave":3, "Fearless":5}),  # 5 tiers, from Fearful to Brave to Fearless
        "optimism": ({"Pessimistic":1, "Optimistic":3, "Pipe Dreamer":5}),  # 5 tiers, from Pessimistic to Optimistic to Pipe Dreamer
        "greed": ({"Largesse":1, "Normal":3, "Avaricious":5}),  # 5 tiers, from Largesse to Avaricious
        "socialibility": ({"Antisocial":1, "Bashful":2 ,"Gregarious":4, "Social":6, "Hypersocial":7}), # 7 tiers, from Antisocial to Bashful to Gregarious to Social to Hypersocial
        "elocution": ({"Stagefright":1, "Orator":3, "Eluctionist":5}),  # 5 tiers, from Stagefright to
        "allure": ({"Repulsive":1, "Charming":4, "Entrancing":7}),  # 7 tiers, from Repulsive to Charming to Attractive
        "humility": ({"Egostigical":1, "Arrogant":3, "Modest":5, "Humble":7, "Submissive":9}), # 9 tiers, from Egostigical (superiority complex) / Arrogant to Modest / Humble to Submissive( or Spineless )
        "partiality": ({"Impartial":1, "Mixed":4, "Partial":7}),  # 7 tiers, from Impartial to Mixed to Partial
        "reliability": ({"Liability":1, "Unreliable":3, "Reliable":5, "Perfect":7}), # 9 tiers, from Unreliable -> Liability to Mixed Reliability to Reliable to Perfect
        "loyalty": ({"Disloyal":1, "Loyal":3, "Obsessed":5, "Undying Bond":7}),  # 7 tiers, from Disloyal to Undying Bond
        "independence": ({"Dire Dependence":1, "Irresponsible":3, "Responsible":5, "Independent":7}),  # 7 tiers, from Dependent to Partial Dependence to Independent
        "introspection": ({"Ignorant":1, "Aware":4, "Self Aware":7}),  # 7 tiers, from Ignorant to X to Self Aware
        "self_control": ({"Disinhibited":1, "Disciplined":3, "Overrestraining":5}),  # 5 tiers, from Disinhibited to Disciplined to Overrestraining Self-censorship
        "lust": ({"Insouciant":1, "Curious":3, "Covetous":5}),  # 5 tiers, from Insouciant to Curious to Covetous
        "stress": ({"Calm":1, "Stressed":3, "Overtaxed":5}),  # 5 tiers, from X to Y to Overtaxed
        "anger": ({"Bothered":1, "Annoyed":3, "Irritated":5, "Enraged":7}),
        "aggresiveness": ({"Contemptuous":1, "Angry":4, "Hostile":7}),  #
        "orderliness": ({"Chaotic":1, "Orderly":4, "Strict":7}),  # from Chaotic to Orderly
        "friendliness": ({"Mean":1, "Nice":4, "Obsequious":7}),  #
        "politeness": ({"Rash":1, "Eloquent":3, "Obsequious":5}),  #
        "bravery": ({"Cowardly":1, "Normal":3, "Relentless":5}),  # Cowardly to Relentless
        "counseling": ({"Avoids Advice":1, "Listens to Advice":3, "Input Dependence":5}),  # Avoids Advice to Input Dependence
        "ambition": ({"Undriven":1, "Ambitious":3, "Relentless":5}),  # from Undriven to Relentless
        "gratitude": ({"Unreciprocating":1, "Fair":3, "Reciprocative":5}),  # Unreciprocating to Fair to Reciprocative
        "modesty": ({"Vain":1, "Modest":3, "Overmodest":5}),  #
        "humor": ({"Uncomedic":1, "Humorous":3, "Zany":5}),  # Uncomedic to Comedic to Zany
        "individuality": ({"Selfless":1, "Individualistic":3, "Egostigical":5}),  # from Selfless to Egostigical
        "perserverance": ({"Vacillative":1, "Determined":3, "Resolute":5}),  # from Vacillative to Resolute
        "recourse": ({"Pessimist":1, "Intermediate":3, "Optimist":5}),  # from Pessimist to Optimist
        "bashfulness": ({"Gutsy":1, "Shy":3, "Timorous":5}),  # from X to Shy to Y
        "tolerance": ({"Defiant":1, "Forbearant":3, "Docile":5}),  # from Defiant to Forbearant to Docile
        "emotional_integrity": ({"Nervous Wreck":1, "Normal":3, "Incredibly Stable":5}),  # 5 tiers, from Nervous Wreck to Incredibly Stable
        "vivaciousness": ({"Dull":1, "Active":3, "Vivacious":5}),  # 5 tiers, from Dull to Active to Vivacious
        "excitement": ({"Boring":1, "Adventurous":3, "Escapade Prone":5}),  # 5 tiers, from Boring to Adventurous to Escapade Prone
        "abstract": ({"Practical":1, "Balanced":3, "Philosophical":5}),  # 5 tiers, from Practical to Philosophical
        "openness": ({"Ignorant":1, "Open Minded":3, "Transparent":5}),  # 5 tiers, from Ignorant to Open Minded to Transparent
        "mercy": ({"Cruel":1, "Balanced":4, "Compassionate":7}),  # Cruel to Compassionate
        "peacefulness": ({"Warmonger":1, "Tranquil":4, "Pacifistic":7}),  # 7 tiers, from Warmonger to Tranquil to Pacifistic
        "demeanor": ({"Anxious":1, "Alert":3, "Calm":5}), # 5 tiers, from Anxious to Calm
        "continuance": ({"Suicidal":1, "Normal":2, "Mortally Aware":3}) # 3 tiers, from Suicidal to Normal to Mortally Aware. Originally self_preservation
### Predefined Personalities
    These are entire personality trait levels and "pure" (more on this below) traits that were already defined. For players who generally want to see more action instead of RPG-style trait selection, this would be your best bet.
### Pure Personality Traits
    These are traits that are rangeless, and consist of a single tier. These have heavier weight than the traits above.
## NPC Relationships
- Varying levels of Association (From Enemy to Associate to Friend)
Levels of Association are the very core of NPC Relationships. How high or low in association that you go may determine general action.
- Friends
Friends are people who are friendly to Characters. They have a high level of association, and with that comes benefits. Characters put their trust in them, and are willing to help them when in need.
- Associates
Associates are people who aren't opposed to Characters, but have a general association with them. They aren't as trusted as Friends, though they may carry their own benefits to Characters.
These are the type that you'd have a professional relationship with, such as Ambassadors to faction.
- Enemies
Enemies are people who are in opposition to other Characters. They have a very low level of association.
- Romantic Interests
The following are romantic associations that the game will recognize:
    - Girlfriends
        A female in an active romantic relationship.
    - Boyfriends
        A male in an active romantic relationship.
- Family Groups
Family elements include the following associations:
    - Grandmothers
        Mothers of parents.
    - Grandfathers
        Fathers of parents.
    - Mothers
        Female parents with children.
    - Fathers
        Male parents with children.
    - Sisters
        Female siblings.
    - Brothers
        Male siblings.
    - Aunts
        The sister of a parent.
    - Uncles
        The brother of a parent.
    - Cousins
        Siblings belonging to a different set of parents, coming from the same grandparents.
    - Spouses
        A member of your marriage relationship.

### Pregnancy
The effects from the pregnant character are as follows:
- Mood swings
- Fast Metabolism
- Occasional Nausea
- Fatigue
- Dexterity Drop
- Decreased Immunity
#### POST PREGNANCY
- Weight Loss
- Mood swings
- Hunger
- Thirst
- Occasional Nausea
#### THE BABY
The baby is a special monster that has only one other stage: Child.
After it reaches age 5, the baby turns into a Child. Memories will quickly and randomly be removed until age 8.

### Worldgen
During worldgen, these family groups can generate. Not all family groups will have all associations.
Notes:
    Outside of parents, no family element can reproduce or have romantic relationships with each other.

## NPC Behavior
### Reactive AI
    - Behavior of AI when experiencing things. 
    - This could be AI reacting to an emote, or an AI reacting to seeing the corpse of a fallen comrade. 
    - For Phase 1, the AI will react to emotes, getting hurt, running out of food and/or water, socializing with other NPCs, seeing monsters, and being hurt.
    - NPCs will wander, looking around for unclaimed food (or claimed food if they're hungry enough) and sources of water. 
    - They will fill up personal liquid containers (bottles, thermoses, flasks) and store preferrably clean water; though this will also depend on intelligence. An AI with the intelligence of or below 3 / is very thirsty will drink anything that is liquid and comestible.

### Tactical AI
    Tactical AI (Often referred to as "Tactical Units") are NPCs that have tactical orders. These orders consist of (but are not limited to) `seeking cover`, `flanking targets`, `grabbing wounded allies`, `guard waypoint`.

    All NPCs with have Tactical AI. Not all NPCs may have 
#### COVER    
    - For combat, depending on IFC, the AI can `scan` for cover and take it.
    - Depending on how intelligent and focused the particular AI is, the choice for cover can range from things that can barely be considered adequate cover, to things that are appropriate for the type of weapon they are up against.
    
    - Example: Let's say an AI is faced with a live grenade three seconds away from an explosion. 
        - The AI would notice this, and quickly attempt to move out of the affected area. 
        - A stressed and less-focused AI would just jump behind anything it can until it hears a boom. 
        - A disciplined AI with a decent amount of focus would leap into appropriate cover, kick it or throw it (if it knew what it was).
    - AI will grab wounded friendlies and bring them behind cover.
        - Using the `cover system`, NPCs in combat will process threats and the viability to recover their wounded comrades. 
    
### Social AI
    - General social behavior of the AI.
    The AI's general social behavior heavily takes from the Personalities & Beliefs stats. 
    - AI will be able to threaten and be threatened.
    **PHASE ONE**
    AI can have specific demands.
# <important TODO stuff goes here>
# Dynamic Factions
## ABSTRACT
Factions are currently relegated to the player's faction (which is automatically generated, whether you wanted one or not) and to several other predefined factions.
Not only are these factions scripted in, but these factions don't do anything gameplay-wise. They have their own elementary property system (don't touch stuff that doesn't belong to you in or around the refugee center); including the locations that they're in (refugee center == free merchant territory).
*Dynamic Factions* seeks to make factions be more interactive in this living, breathing open world by giving them the ability to interact (ally, trade, wage war on...) other entities and factions.
|||
||| Upon release, the player will not automatically have a faction ("Your Followers"). You will be able to create a faction in the Factions menu (default: #).
## FACTION PROPERTY
Faction Property refers to land, buildings, vehicles, owned creatures, items, and other factions that are owned by this faction.
Factions will be able to claim property as it expands, and property disputes may occur. All disputes may end with a peaceful agreement or a conflict.
Disputes that end peacefully may have been peaceful for the following reasons:
- Low faction Wellness score

## FACTION TYPE
- De-Facto
De-Facto factions are factions that lack a hierarchy or and clear goal. They are likely made for the purpose of grouping up.
Personality-traits wise, those with moderate to high social need are very likely to join other Characters, and if those Characters already have a unorganized faction, it could hairball into a much greater, unorganized collection of Characters.
- General
A general faction is more organized than a De-Facto faction, though have no specific goal. A loose collective, these factions may do a bit of everything just to survive.
These factions may have a clear hierarchy, with their own leadership. Being a general-purpose collective, general factions could evolve into Social factions if the overall faction morale is high (>59%)
- Corporate
Corporate factions are factions that seek to make a profit. They can be `multi-industry` or `single-industry`.
`multi-industry` - factions have no specific industry. They simply wish to turn a profit.
`single-industry` - factions that work in a specific industry.
Corporate factions, like any other faction, can be created out of necessity.
Corporate diplomacy between Corpo Factions legally do not get as heated as diplomacy between actual political
- Social
Social factions are factions that have a focus on establishing their own society. Of all factions, they are the most organized, and the most territorial. They are not focused on turning a profit, rather, they are focused on the well-being of their citizens, property and territory.
- Coalition
A coalition is a group of two or more factions. They are property of an umbrella faction. Factions that are failing (low morale, low resources) will ask to go under the wing of other factions; any faction will suite (as long as they are numerically higher in well-being), though the factions highest in well-being will be chosen over others.
## FACTION DIPLOMACY
- Peace & War
Factions ultimately have two states: They're at peace, or they're at war. Peacetime specifically deals with a lack on conflict. Wartime deals with highly unfavorable / questionable political actions against factions.
- Negotiation
## PLANNED FACTIONS
# Dynamic Economy
## ABSTRACT
|||Reciv Era marks the beginning of prices to return to pre-apocalypse prices. Slowly, as more groups start to form, prices go back to pre-apocalypse prices, percentage-wise.
- When trains get worked on, a whole plethora of Railroad-based factions will spring up; factions could also use railroads as transport routes.
- Traders can travel and temporarily settle in places that have had high NPC traffic.
- Traders will prefer to hire security, and as such, will often have a security detail.
- Price haggling, utilizes IFC, emotion, fatigue level, mood & stress IEFMS
- Beggars that actually do something-- whether that's using their donation money to better themselves or to buy drugs.
# Story Mode
## ABSTRACT
Story Mode makes Cataclysm: Dark Days Ahead - Delta Fork oriented towards more linear gameplay, with a focus on stories and dialogue.
## SCREEN EFFECTS
- Actual images will be rendered to the "Play" section of the screen (not the right sidepanel with info on it)
- Screen shake effect
- VHS / Camcorder Overlay
- More defined Checkpoints system
