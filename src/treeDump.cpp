#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "treeDump.h"

static int firstRank = 1;

static void dumpTheSortedNodeInFile( const node_t* node, FILE* fileForWrite );

static void dumpTheSortedTreeInFile( const tree_t* tree, FILE* fileForWrite );

void dumpNode( node_t* node, int rank, FILE* treeFile ){
    assert( node );
    assert( treeFile );

    fprintf( treeFile, "\tnode%lx [shape=\"plain\"; style =\"filled\"; fillcolor =\"azure3\"; label = "
                        "<<table><tr><td> %p </td></tr> <tr><td> " treeValueFormat "</td></tr> ",
                        ( unsigned long )node, node, node->data  );

    if( node->left ){
        fprintf( treeFile, "<tr><td> %p </td></tr>", node->left );
    }
    else{
        fprintf( treeFile, "<tr><td> NULL </td></tr>" );
    }

    if( node->right ){
        fprintf( treeFile, "<tr><td> %p </td></tr>", node->right );
    }
    else{
        fprintf( treeFile, "<tr><td> NULL </td></tr>" );
    }

    fprintf( treeFile, "</table>>;color = \"red\"];\n" );

    fprintf( treeFile, "\t{\n"
                       "\t\trank = %d;\n"
                       "\t\tnode%lx;\n"
                       "\t}\n",
                       rank, ( unsigned long )node );

    if( node->left ){
        fprintf( treeFile, "\t\tnode%lx;\n"
                            "\tnode%lx->node%lx[color = \"orange\"];\n",
                            ( unsigned long )node->left, ( unsigned long )node, ( unsigned long )node->left );
        dumpNode( node->left, rank + 1, treeFile );
    }
    if( node->right ){
        fprintf( treeFile, "\t\tnode%lx;\n"
                           "\tnode%lx->node%lx[color = \"orange\"];\n",
                           ( unsigned long )node->right, ( unsigned long )node, ( unsigned long )node->right );
        dumpNode( node->right, rank + 1, treeFile );
    }

}

treeErrors dumpTree( tree_t* tree ){
    assert( tree );

    FILE* treeFile = fopen( "treeDump.txt", "w" );

    if( treeFile == NULL ){
        return ERROR_OF_OPEN_FILE;
        fclose( treeFile );
    }

    fprintf( treeFile,  "digraph G{\n"
                        "\trankdir = TB;\n"
                        "\tnode[shape = \"hexagon\", color = \"black\", fontsize = 14, shape = record ];\n"
                        "\tedge[color = \"red\", fontsize = 12];\n" );

    dumpNode( tree->rootTree, firstRank, treeFile );

    fprintf( treeFile, "}" );

    fclose( treeFile );

    system("dot treeDump.txt -Tpng -o treeDump.png");

    //HTML

    FILE* htmlDump = fopen( "treeDump.html", "w" );
    if( htmlDump == NULL ){
        return ERROR_OF_OPEN_FILE;
    }

    fprintf( htmlDump, "<pre>\n"
                       "<h1> <font color=red> TREE DUMP </font>  </h1>"
                       "\n\n"
                       "<h1> TREE { %s:%s:%d } </h1>\n\n", __FILE__, __func__, __LINE__ );

    fprintf( htmlDump, "<h2 style = \"color: green;\">tree: \n");
    dumpTreeInFile( tree, htmlDump );


    fprintf( htmlDump, "</h2>\n\n<h2 style = \"color: orange;\">sorted tree: \n" );
    dumpTheSortedTreeInFile( tree, htmlDump );

    fprintf( htmlDump, "</h2>\n\n<h1>Image:</h1>\n"
                       "<img src=treeDump.png width = 2000px>\n\n");

    fclose( htmlDump );

    return CORRECT_TREE;
}

void dumpNodeInFile( const node_t* node, FILE* fileForPrint ){
    assert( node );
    assert( fileForPrint );

    fprintf( fileForPrint, "(\"" treeValueFormat "\"", node->data );

    if( node->left ){
        dumpNodeInFile( node->left, fileForPrint);
    }
    else{
        fprintf( fileForPrint, "nil" );
    }
    if( node->right ){
        dumpNodeInFile( node->right, fileForPrint );
    }
    else{
        fprintf( fileForPrint, "nil" );
    }

    fprintf( fileForPrint, ")" );
}

void dumpTreeInFile( const tree_t* tree, FILE* fileForPrint ){
    assert( tree );
    assert( fileForPrint );

    dumpNodeInFile( tree->rootTree, fileForPrint );
}

static void dumpTheSortedNodeInFile( const node_t* node, FILE* fileForPrint ){
    assert( node );
    assert( fileForPrint );

    if( node->left ){
        dumpTheSortedNodeInFile( node->left, fileForPrint);
    }

    fprintf( fileForPrint, treeValueFormat " ", node->data );

    if( node->right ){
        dumpTheSortedNodeInFile( node->right, fileForPrint);
    }
}

static void dumpTheSortedTreeInFile( const tree_t* tree, FILE* fileForPrint ){
    assert( tree );
    assert( fileForPrint );

    dumpTheSortedNodeInFile( tree->rootTree, fileForPrint );
}
