// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __PROTOFUN_HXX__
#define __PROTOFUN_HXX__

#include <ostream>
#include <string>
#include <vector>

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"


namespace
{

    class FunctionsCollector : public clang::RecursiveASTVisitor<FunctionsCollector>
    {
        clang::CompilerInstance & CI;
        const std::string root;
        const std::string lock;
        const std::string out;
        std::vector<std::tuple<std::string, std::string, unsigned>> info;

    public:

        FunctionsCollector(clang::CompilerInstance & __CI, const std::string & __root, const std::string & __lock, const std::string & __out);

        std::pair<std::string, unsigned> getFileLine(const clang::Decl * decl) const;
        void handleFunctionDecl(clang::FunctionDecl * decl);
        bool VisitClassTemplateDecl(clang::ClassTemplateDecl * decl);
        bool VisitFunctionDecl(clang::FunctionDecl * decl);
        void push_info();
        void print_info(std::ostream & os) const;

    private:

        static bool startswith(const std::string & a, const std::string & b);
    };

    class FunctionsCollectorConsumer : public clang::ASTConsumer
    {
        clang::CompilerInstance & CI;
        FunctionsCollector visitor;

    public:

        FunctionsCollectorConsumer(clang::CompilerInstance & __CI, const std::string & root, const std::string & lock, const std::string & out);
        virtual ~FunctionsCollectorConsumer();

        virtual void HandleTranslationUnit(clang::ASTContext & ctxt);
        virtual bool shouldSkipFunctionBody(clang::Decl * decl);
    };


    class FunctionsCollectorAction : public clang::PluginASTAction
    {
        std::string root;
        std::string lock;
        std::string out;

    protected:

        std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, llvm::StringRef) override;
        bool ParseArgs(const clang::CompilerInstance & CI, const std::vector<std::string> & args) override;

        // Automatically run the plugin after the main AST action
        PluginASTAction::ActionType getActionType() override;
    };

}

#endif // __PROTOFUN_HXX__
