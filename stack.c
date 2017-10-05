#include "stack.h"


struct _Stack {

      /* COMPONENTES QUE UTILICES PARA IMPLEMENTAR LA PILA COMO POR EJEMPLO top PARA APUNTAR A LA CIMA O item PARA GUARDAR LOS DATOS EN LA PILA */
      /* CUIDADO... EL TIPO DE DATO GUARDADO EN LA PILA (POR EJEMPLO SI item ES UNA COLECCION) DEBE SER void * (LA COLECCIÓN LO SERÁ DE PUNTEROS TIPO void *  */


      /* ESTOS SON LOS PUNTEROS A LAS FUNCIONES NECESARIAS DE MANIPULACIÓN DEL DATO */
    int top;
    void **items;
    destroy_element_function_type   destroy_element_function;
    copy_element_function_type      copy_element_function;
    print_element_function_type     print_element_function;
};



/**------------------------------------------------------------------
Inicializa la pila reservando memoria y almacenando los
tres punteros a funci�n pasados como par�metro
(el primero para destruir elementos, el segundo para copiar elementos
y el tercero para imprimir elementos).
Salida: NULL si ha habido error o la pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
  Stack *s = NULL;

  s = (Stack*)malloc(sizeof(Stack));

  if(!s)
    return NULL;

  s->top = -1;
  s->items = NULL;
  s->destroy_element_function = f1;
  s->copy_element_function = f2;
  s->print_element_function = f3;

  return s;
}

/**------------------------------------------------------------------
Elimina la pila
Entrada: la pila que se va a eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack *s){
  int i;

  if(!s) return;

  for(i = s->top; i >= 0; i--){
    s->destroy_element_function(s->items[i]);
  }
  free(s->items);
  free(s);

  return;
}
/**------------------------------------------------------------------
Inserta un elemento en la pila.
Entrada: un elemento y la pila donde insertarlo.
Salida: NULL si no logra insertarlo o la pila resultante si lo logra
------------------------------------------------------------------*/
Stack * stack_push(Stack *s, const void *item){

  if(!s || s->top == MAXSTACK - 1)
    return NULL;

  s->top ++;
  s->items = realloc(s->items, (s->top+1)*sizeof(s->items[0]));

  if(!s->items)
    return NULL;

  s->items[s->top] = s->copy_element_function(item);

  return s;
}
/**------------------------------------------------------------------
Extrae un elemento en la pila.
Entrada: la pila de donde extraerlo.
Salida: NULL si no logra extraerlo o el elemento extraido si lo logra.
Notese que la pila quedara modificada
------------------------------------------------------------------*/
void * stack_pop(Stack *s){
  void *item;

  if(!s || s->top < 0)
    return NULL;

  item = s->items[s->top];

  s->items = realloc(s->items, (s->top)*sizeof(s->items[0]));

  if(!s->items)
    return NULL;

  s->top--;

  return item;
}
/**------------------------------------------------------------------
Copia un elemento (reservando memoria) sin modificar el top de la pila.
Entrada: la pila de donde copiarlo.
Salida: NULL si no logra copiarlo o el elemento si lo logra
------------------------------------------------------------------*/
void * stack_top(const Stack *s){
  if(!s)
    return NULL;

  return s->copy_element_function(s->items[s->top]);
}

/**------------------------------------------------------------------
Comprueba si la pila esta vacia. Entrada: pila.
Salida: TRUE si esta vacia o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *s){
  if(!s)
    return FALSE;

  if(s->top > -1)
    return FALSE;
  return TRUE;

}
/**------------------------------------------------------------------
Comprueba si la pila esta llena.
Entrada: pila.
Salida: TRUE si esta llena o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isFull(const Stack * s){
  if (!s)
    return FALSE;
  return s->top == MAXSTACK-1;
}
/**------------------------------------------------------------------
Imprime toda la pila, colocando el elemento en la cima al principio de
la impresion (y un elemento por linea).
Entrada: pila y fichero donde imprimirla.
Salida: Devuelve el numero de caracteres escritos.
------------------------------------------------------------------*/
int stack_print(FILE* fp, const Stack* s){
  int i, nchar = 0;

  if(!fp || !s)
    return -1;

  for(i = 0; i <= s->top; i++){
    nchar += s->print_element_function(fp, s->items[i]);
  }

  return nchar;

}


int stack_size(const Stack* s){
  return s->top+1;
}
