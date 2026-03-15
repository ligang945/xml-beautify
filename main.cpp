/**
 * @author ligang
 * @date 20190228
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tinyxml2.h"

using namespace tinyxml2;

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [OPTIONS] INPUT_FILE\n\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -h, --help              Show this help message and exit\n");
    fprintf(stderr, "  -o, --output FILE       Output file (default: print to stdout)\n");
    fprintf(stderr, "  -i, --indent NUM        Indentation spaces (default: 4)\n");
    fprintf(stderr, "  -v, --verbose           Enable verbose output\n");
    fprintf(stderr, "  --inplace               Edit input file in place (overwrites original)\n");
    fprintf(stderr, "\nExamples:\n");
    fprintf(stderr, "  %s input.xml                    Print to stdout\n", prog_name);
    fprintf(stderr, "  %s input.xml -o output.xml      Save to output.xml\n", prog_name);
    fprintf(stderr, "  %s input.xml --inplace           Edit in place\n", prog_name);
    fprintf(stderr, "  %s input.xml -i 2                Use 2 spaces indent\n", prog_name);
}

int main(int argc, char *argv[]) {
    const char *input_file = NULL;
    const char *output_file = NULL;
    int indent = 4;
    bool verbose = false;
    bool inplace = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --output requires a file argument\n");
                return 1;
            }
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--indent") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: --indent requires a number argument\n");
                return 1;
            }
            indent = atoi(argv[++i]);
            if (indent < 0) {
                fprintf(stderr, "Error: indent must be a non-negative number\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "--inplace") == 0) {
            inplace = true;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Error: unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        } else {
            if (input_file != NULL) {
                fprintf(stderr, "Error: multiple input files specified\n");
                return 1;
            }
            input_file = argv[i];
        }
    }

    if (input_file == NULL) {
        fprintf(stderr, "Error: no input file specified\n");
        print_usage(argv[0]);
        return 1;
    }

    if (inplace && output_file != NULL) {
        fprintf(stderr, "Error: cannot use --inplace with --output\n");
        return 1;
    }

    XMLDocument doc;
    XMLError error = doc.LoadFile(input_file);

    if (error != XML_SUCCESS) {
        fprintf(stderr, "Error: failed to load file '%s': %s\n",
                input_file, doc.ErrorStr());
        return 1;
    }

    if (verbose) {
        fprintf(stderr, "Loaded XML file: %s\n", input_file);
    }

    doc.SetIndentString(" ");
    for (int i = 0; i < indent; i++) {
        doc.IndentString() += " ";
    }

    if (inplace || output_file != NULL) {
        const char *dest = inplace ? input_file : output_file;
        error = doc.SaveFile(dest);

        if (error != XML_SUCCESS) {
            fprintf(stderr, "Error: failed to save file '%s': %s\n",
                    dest, doc.ErrorStr());
            return 1;
        }

        if (verbose) {
            fprintf(stderr, "Saved XML to: %s\n", dest);
        }
    } else {
        XMLPrinter printer(stdout);
        printer.SetIndent("");
        for (int i = 0; i < indent; i++) {
            printer.PushIndent();
        }
        doc.Print(&printer);
    }

    return 0;
}
