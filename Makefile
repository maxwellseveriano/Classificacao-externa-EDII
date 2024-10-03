all: geracao_particoes intercalacao_particao

geracao_particoes:
	$(MAKE) -C geracao-de-particoes

intercalacao_particao:
	$(MAKE) -C intercalacao

run: all
	$(MAKE) -C geracao-de-particoes run
	$(MAKE) -C intercalacao run

