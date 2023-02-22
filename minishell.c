/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:18:33 by aliburdi          #+#    #+#             */
/*   Updated: 2023/02/22 17:20:14 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("Current working directory: %s\n", path);
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	initializer(t_struct *m)
{
	m->input = NULL;
	m->args = NULL;
	m->dir = getenv("HOME");
	if (m->dir == NULL)
		perror(m->dir);
	m->arg_count = 0;
	m->status = 0;
	m->i = 0;
	m->start = 0;
	m->quotes = 0;
	m->pid = 0;
}

int	main()
{
	t_struct	m;
	int			i;
	pid_t		pid;
	char		path[1024];
	char		*envp;

	i = 0;
	envp = NULL;
	initializer(&m);
	while (1)
	{
		write(STDOUT_FILENO, "minishell> ", ft_strlen("minishell> "));
		m.input = readline(STDIN_FILENO); //get_next_line legge l'input dell'utente da stdin e lo salva nella variabile m.input.
		m.args = (char **)malloc(sizeof(char *) * (m.arg_count + 1));//alloca la memoria necessaria per contenere gli argomenti che verranno estratti dall'input.
/*controlla se il carattere corrente è una virgoletta doppia o singola. Se sì, imposta il valore della variabile "m.quotes" a vero o falso a seconda che ci sia una citazione aperta o chiusa. Questo aiuta a riconoscere se una parola è all'interno di una citazione o no.
Se il carattere corrente è uno spazio e non si trova all'interno di una citazione, il codice prende tutti i caratteri tra l'inizio dell'ultima parola (m.start) e la posizione corrente (i), li copia in un nuovo elemento dell'array "m.args" e aggiorna il contatore delle parole (m.arg_count). 
Infine, il codice imposta l'inizio della prossima parola (m.start) alla posizione successiva al carattere spazio e continua con la scansione della stringa di input.
Il codice usa anche la funzione "malloc" per allocare memoria dinamicamente per ogni nuova parola, e la funzione "realloc" per espandere dinamicamente l'array "m.args" quando si aggiunge una nuova parola.*/
		while (m.input[i])
		{
			if (m.input[i] == '\"' || m.input[i] == '\'')
				m.quotes = !m.quotes;
			else if (m.input[i] == ' ' && !m.quotes)
			{
				m.args[m.arg_count] = (char *)malloc(i - m.start + 1);
				ft_strncpy(m.args[m.arg_count], m.input + m.start, i - m.start);
				m.args[m.arg_count][i - m.start] = '\0';
				m.arg_count++;
				m.args = (char **)ft_realloc(m.args, sizeof(char *) * (m.arg_count + 2));
				m.start = i + 1;
			}
			i++;
		}
		/*ensomma sto codice aggiunge una nuova parola alla fine dell'array "m.args" solo se l'indice corrente i è maggiore dell'indice di inizio della parola m.start. cioè solo le parole complete (ovvero quelle che non sono interrotte da una virgoletta) saranno aggiunte all'array.
		Alla fine del ciclo while, l'array "m.args" conterrà tutte le parole separate trovate nella stringa di input (se spera).*/
		if (i > m.start)// controlla se il ciclo while ha trovato una parola completa
		{
		m.args[m.arg_count] = (char *) malloc(sizeof(char) * (i - m.start + 1));// dimensione dell'elemento viene calcolata come la differenza tra l'indice corrente i e l'indice di inizio della parola m.start, più uno per il carattere di terminazione della stringa ('\0').
		ft_strncpy(m.args[m.arg_count], m.input + m.start, i - m.start);//Copia la parola appena trovata dalla stringa di input nell'elemento dell'array "m.args"
		m.args[m.arg_count][i - m.start] = '\0';//Aggiunge il carattere di terminazione della stringa ('\0') all'ultima posizione dell'elemento dell'array "m.args" per assicurarsi che la parola sia correttamente terminata aka trust issues
		m.arg_count++;
		m.args = (char **)ft_realloc(m.args, sizeof(char *) * (m.arg_count + 1));//spandere dinamicamente l'array "m.args" in modo che possa contenere l'elemento aggiunto 
		}
		m.args[m.arg_count] = NULL;//Termina l'array degli argomenti con NULL
		// Esegue il comando
		if (m.arg_count > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				// printf("%s\n%s\n", m.args[0], m.args[1]); //un print giusto per controllare i primi 2 argomenti che gli arrivano(ogni tanto scazza e si perde le prime 3 lettere xd)
				if (ft_strcmp(m.args[0], "pwd") == 0) //vedo se la prima istruzione é pwd provo a eseguirla se non va c'é il perror
				{
					if (getcwd(path, sizeof(path)) != NULL)
						printf("Current working directory: %s\n", path);
					else
					{
						perror("getcwd() error");
						return (EXIT_FAILURE);
					}
				}
				else if (ft_strcmp(m.args[0], "cd") == 0)//vede se c'é cd e se dopo c'é un altro argomento se si, prova a fare il chdir altrimenti printa errori (attualmente non riesce mai a cambiare dir)
				{
					if (m.args[1] == NULL)
						printf("cd: expected argument to \"cd\"\n");
					else if (m.args[1])
						chdir(m.args[1]);
				}
				else
				{
					execve(m.args[0], m.args, &envp);
					perror("execve");
				}
			}
			else if (pid < 0)//Se la creazione del processo figlio fallisce, poro figlio
				perror("fork");//Stampa eventuali errori di creazione del processo
			else
				waitpid(pid, &m.status, 0);//Attende la terminazione del processo figlio
		}
		free(m.input);
		i = 0; //resetta il contatore degli argomenti
		while (i < m.arg_count)
		{
			free(m.args[i]);
			i++;
		}
		free(m.args);
		//Resetta il conteggio degli argomenti
		m.arg_count = 0;
	}
	return (0);
}
