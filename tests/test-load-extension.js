sys = require('sys');
fs = require('fs');
path = require('path');

TestSuite = require('async-testing/async_testing').TestSuite;
sqlite = require('sqlite3_bindings');

puts = sys.puts;
inspect = sys.inspect;

var name = "Load extensions";
var suite = exports[name] = new TestSuite(name);

var tests = [
  { 'create in memory database object': 
    function (assert, finished) {
      this.db.open(':memory:', function (error) {
        assert.ok(!error)
        finished();
      });
    }
  }
, { 'enable and disable extension loading': 
    function (assert, finished) {
      var self = this;
      this.db.open(':memory:', function (error) {
        if (error) throw error;

        // use a query that will never return rows
        self.db.enableLoadExtension(1,
          function (error, statement) {
            if (error) throw error;
            assert.equal(error, undefined)

            // no statement will be returned here
            assert.ok(!statement)
            finished();
          });
      });
    }
  }
, { 'load an extension': 
    function (assert, finished) {
      var self = this;
      this.db.open(':memory:', function (error) {
        if (error) throw error;
        
        // use a query that will never return rows
        self.db.enableLoadExtension(1,
          function (error, statement) {
            if (error) throw error;
            assert.equal(error, undefined)

            // no statement will be returned here
            assert.ok(!statement)
            finished();
          });

        // use a query that will never return rows
        self.db.loadExtension("/usr/local/lib/libspatialite.dylib",
          function (error, statement) {
            if (error) throw error;
            assert.equal(error, undefined)

            // no statement will be returned here
            assert.ok(!statement)
            finished();
          });
      });
    }
  }
];

for (var i=0,il=tests.length; i < il; i++) {
  suite.addTests(tests[i]);
}

var currentTest = 0;
var testCount = tests.length;

suite.setup(function(finished, test) {
  this.db = new sqlite.Database();
  finished();
});
suite.teardown(function(finished) {
  if (this.db) this.db.close(function (error) {
                               finished();
                             });
  ++currentTest == testCount;
});

if (module == require.main) {
  suite.runTests();
}
